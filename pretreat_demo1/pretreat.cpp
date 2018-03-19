#include "pretreat.h"
#include "ui_pretreat.h"

#include <X11/Xlib.h>

#include "HalconCpp.h"
#include "HDevThread.h"
/*


*/

HObject ho_Image;

HObject ho_ImageLaplace;
HObject  ho_ImageInvert;
HObject  ho_EdgeAmplitude;
HObject  ho_ImageSmooth;
HObject  ho_SE, ho_ImageErosion,ho_ImageDilation;
HObject ho_Highpass, ho_ImageMean,ho_ImageMedian;


HTuple hv_Width, hv_Height, hv_WindowHandle=0, widid2;
long widid;

PreTreat::PreTreat(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PreTreat)
{
    ui->setupUi(this);
    globalMark=0;
}

PreTreat::~PreTreat()
{
    delete ui;
}

void QWidget::closeEvent(QCloseEvent *event)
{
    if(hv_WindowHandle!=0)
    {
        HDevWindowStack::Pop();
        CloseWindow(hv_WindowHandle);
        hv_WindowHandle=0;
    }
    QApplication *app;
    app->exit(0);
}

void PreTreat::on_OpenImageButton_clicked()  //打开图像文件
{
    ui->label->clear();
    QString fileName = QFileDialog::getOpenFileName(this,tr("open image file"), "./", tr("Image files(*.jpg *.png);;All files (*.*)"));
                                                        //窗口文字               默认目录       筛选后缀
    widid=this->winId();
    widid2=widid;
    ReadImage(&ho_Image, HTuple(fileName.toStdString().c_str()));
  //  OpenWindow(ui->graphicsView->x(),ui->graphicsView->y(),ui->graphicsView->width(),ui->graphicsView->height(),widid2,"","",&hv_WindowHandle);

    OpenWindow(0,0,ui->graphicsView->width(),ui->graphicsView->height(),widid2,"","",&hv_WindowHandle);
    HDevWindowStack::Push(hv_WindowHandle);
    if(HDevWindowStack::IsOpen())
    {
        DispObj(ho_Image,HDevWindowStack::GetActive());
        ui->label->setText(fileName);
        globalMark=1;
    }
}

void PreTreat::on_SaveImageButton_clicked()//保存图像文件
{
    if(globalMark==1)
    {
         QString filePath;
         QDateTime time=QDateTime::currentDateTime();
         QString saveName=time.toString("yyyyMMdd_hhmmss");
         filePath=QDir::homePath();//QFileDialog::getExistingDirectory(this,"");

         QString savePath=QString("%1/%2.jpg").arg(filePath).arg(saveName);
         ui->label->setText(savePath);
         WriteImage(ho_Image, "jpeg", 0, HTuple(savePath.toStdString().c_str()));
    }
    else
    {
        QMessageBox::information(this,"Message","Save image failed!");
    }
}

void PreTreat::on_LaplaceButton_clicked()
{
    widid=this->winId();
    widid2=widid;
    Laplace(ho_Image, &ho_ImageLaplace, "absolute", 3, "n_4");
    ho_Image=ho_ImageLaplace;
    if(hv_WindowHandle!=0)
    {
        HDevWindowStack::Pop();
        CloseWindow(hv_WindowHandle);
        hv_WindowHandle=0;
    }
    OpenWindow(ui->graphicsView->y(),ui->graphicsView->x(),ui->graphicsView->width(),ui->graphicsView->height(),widid2,"","",&hv_WindowHandle);
    HDevWindowStack::Push(hv_WindowHandle);
    if(HDevWindowStack::IsOpen())
        DispObj(ho_Image,HDevWindowStack::GetActive());
}

void PreTreat::on_pushButton_clicked()
{
    widid=this->winId();
    widid2=widid;
  //  Laplace(ho_Image, &ho_ImageLaplace, "absolute", 3, "n_4");
    InvertImage(ho_Image, &ho_ImageInvert);  //反色处理
    ho_Image=ho_ImageInvert;                //传递
    if(hv_WindowHandle!=0)
    {
        HDevWindowStack::Pop();
        CloseWindow(hv_WindowHandle);
        hv_WindowHandle=0;
    }
    OpenWindow(ui->graphicsView->y(),ui->graphicsView->x(),ui->graphicsView->width(),ui->graphicsView->height(),widid2,"","",&hv_WindowHandle);
    HDevWindowStack::Push(hv_WindowHandle);
    if(HDevWindowStack::IsOpen())
        DispObj(ho_Image,HDevWindowStack::GetActive());
}

void PreTreat::on_SobelButton_clicked()
{
    widid=this->winId();
    widid2=widid;
    SobelAmp(ho_Image, &ho_EdgeAmplitude, "sum_abs", 3); //sobel处理
    ho_Image=ho_EdgeAmplitude;                //传递
    if(hv_WindowHandle!=0)
    {
        HDevWindowStack::Pop();
        CloseWindow(hv_WindowHandle);
        hv_WindowHandle=0;
    }
    OpenWindow(ui->graphicsView->y(),ui->graphicsView->x(),ui->graphicsView->width(),ui->graphicsView->height(),widid2,"","",&hv_WindowHandle);
    HDevWindowStack::Push(hv_WindowHandle);
    if(HDevWindowStack::IsOpen())
        DispObj(ho_Image,HDevWindowStack::GetActive());
}

void PreTreat::on_SmoothButton_clicked()
{
    widid=this->winId();
    widid2=widid;
   SmoothImage(ho_Image, &ho_ImageSmooth, "gauss", 5);//平滑
    ho_Image=ho_ImageSmooth;                //传递
    if(hv_WindowHandle!=0)
    {
        HDevWindowStack::Pop();
        CloseWindow(hv_WindowHandle);
        hv_WindowHandle=0;
    }
    OpenWindow(ui->graphicsView->y(),ui->graphicsView->x(),ui->graphicsView->width(),ui->graphicsView->height(),widid2,"","",&hv_WindowHandle);
    HDevWindowStack::Push(hv_WindowHandle);
    if(HDevWindowStack::IsOpen())
        DispObj(ho_Image,HDevWindowStack::GetActive());
}

void PreTreat::on_ErosionButton_clicked()
{
    widid=this->winId();
    widid2=widid;
    GenDiscSe(&ho_SE, "byte", 8, 8, 0);
     GrayErosion(ho_Image, ho_SE, &ho_ImageErosion);//腐蚀
     ho_Image=ho_ImageErosion;                //传递
    if(hv_WindowHandle!=0)
    {
        HDevWindowStack::Pop();
        CloseWindow(hv_WindowHandle);
        hv_WindowHandle=0;
    }
    OpenWindow(ui->graphicsView->y(),ui->graphicsView->x(),ui->graphicsView->width(),ui->graphicsView->height(),widid2,"","",&hv_WindowHandle);
    HDevWindowStack::Push(hv_WindowHandle);
    if(HDevWindowStack::IsOpen())
        DispObj(ho_Image,HDevWindowStack::GetActive());
}


void PreTreat::on_DilationButton_clicked()
{
    widid=this->winId();
    widid2=widid;
    GenDiscSe(&ho_SE, "byte", 8, 8, 0);
     GrayDilation(ho_Image, ho_SE, &ho_ImageDilation);//腐蚀
     ho_Image=ho_ImageDilation;                //传递
    if(hv_WindowHandle!=0)
    {
        HDevWindowStack::Pop();
        CloseWindow(hv_WindowHandle);
        hv_WindowHandle=0;
    }
    OpenWindow(ui->graphicsView->y(),ui->graphicsView->x(),ui->graphicsView->width(),ui->graphicsView->height(),widid2,"","",&hv_WindowHandle);
    HDevWindowStack::Push(hv_WindowHandle);
    if(HDevWindowStack::IsOpen())
        DispObj(ho_Image,HDevWindowStack::GetActive());
}

void PreTreat::on_HighpassButton_clicked()
{
    widid=this->winId();
    widid2=widid;
    GenDiscSe(&ho_SE, "byte", 8, 8, 0);
     HighpassImage(ho_Image, &ho_Highpass, 19, 19);
     ho_Image=ho_Highpass;                //传递
    if(hv_WindowHandle!=0)
    {
        HDevWindowStack::Pop();
        CloseWindow(hv_WindowHandle);
        hv_WindowHandle=0;
    }
    OpenWindow(ui->graphicsView->y(),ui->graphicsView->x(),ui->graphicsView->width(),ui->graphicsView->height(),widid2,"","",&hv_WindowHandle);
    HDevWindowStack::Push(hv_WindowHandle);
    if(HDevWindowStack::IsOpen())
        DispObj(ho_Image,HDevWindowStack::GetActive());
}

void PreTreat::on_LowpassButton_clicked()
{
    widid=this->winId();
    widid2=widid;
    GenDiscSe(&ho_SE, "byte", 8, 8, 0);
      MeanImage(ho_Image, &ho_ImageMean, 19, 19);
    ho_Image=  ho_ImageMean;              //传递

    if(hv_WindowHandle!=0)
    {
        HDevWindowStack::Pop();
        CloseWindow(hv_WindowHandle);
        hv_WindowHandle=0;
    }
    OpenWindow(ui->graphicsView->y(),ui->graphicsView->x(),ui->graphicsView->width(),ui->graphicsView->height(),widid2,"","",&hv_WindowHandle);
    HDevWindowStack::Push(hv_WindowHandle);
    if(HDevWindowStack::IsOpen())
        DispObj(ho_Image,HDevWindowStack::GetActive());
}

void PreTreat::on_MedianpassButton_clicked()
{
    widid=this->winId();
    widid2=widid;
    GenDiscSe(&ho_SE, "byte", 8, 8, 0);
  MedianImage(ho_Image, &ho_ImageMedian, "circle", 3, "continued");
     ho_Image=  ho_ImageMedian;              //传递
    if(hv_WindowHandle!=0)
    {
        HDevWindowStack::Pop();
        CloseWindow(hv_WindowHandle);
        hv_WindowHandle=0;
    }
    OpenWindow(ui->graphicsView->y(),ui->graphicsView->x(),ui->graphicsView->width(),ui->graphicsView->height(),widid2,"","",&hv_WindowHandle);
    HDevWindowStack::Push(hv_WindowHandle);
    if(HDevWindowStack::IsOpen())
        DispObj(ho_Image,HDevWindowStack::GetActive());
}
