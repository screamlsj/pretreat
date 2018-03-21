#include "pretreat.h"
#include "ui_pretreat.h"

#include <X11/Xlib.h>

#include "HalconCpp.h"
#include "HDevThread.h"



HObject ho_Image;

HObject ho_ImageLaplace;
HObject  ho_ImageInvert;
HObject  ho_EdgeAmplitude;
HObject  ho_ImageSmooth;
HObject  ho_SE, ho_ImageErosion,ho_ImageDilation;
HObject ho_Highpass, ho_ImageMean,ho_ImageMedian;
HObject ho_Region,ho_ConnectedRegions,ho_RegionImage;

HTuple hv_Width, hv_Height, hv_WindowHandle=0, widid2;
long widid;

QString savePath;
QString saveName;
QString fileName;
QString middleSavePath="/home/lsj/workspace/qt/pretreat_demo1/pictures/middle_pictures";
//暂时手动设置中间图片存储路径。。。有个坑：必须要加/home才是绝对路径
QString middlePictureName="mp";
int middlePictureId;

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
   // delete image;
}

void PreTreat::showPicture(Ui::PreTreat*PT,QString filename) //在graphicsView里显示图像
{
    QImage *image;

    image = new QImage();
    //int width,height;

    if(image->load(filename))//直接通过文件名获取图片
    {
//        width=image->width();
//        height=image->height();
                QGraphicsScene *scene = new QGraphicsScene;
                scene->addPixmap(QPixmap::fromImage(*image));
                PT->graphicsView->setScene(scene);
               // PT->graphicsView->resize(width + 10, height + 10);
                PT->graphicsView->show();
    }
}

void PreTreat::on_OpenImageButton_clicked()  //打开图像文件
{
    ui->label->clear();
    fileName = QFileDialog::getOpenFileName(this,tr("open image file"), "./", tr("Image files(*.jpg *.png);;All files (*.*)"));
                                                        //窗口文字         默认目录       筛选后缀
    widid=this->winId();
    widid2=widid;
    ReadImage(&ho_Image, HTuple(fileName.toStdString().c_str()));
    GetImageSize(ho_Image,&hv_Width,&hv_Height);
    showPicture(ui,fileName);
    ui->label->setText(fileName);

    //globalMark部分待添加
    globalMark=1;
    middlePictureId=1;
}

void PreTreat::on_SaveImageButton_clicked()//保存图像文件
{
    if(globalMark==1)
    {
         QString filePath;
         QDateTime time=QDateTime::currentDateTime();
         saveName=time.toString("yyyyMMdd_hhmmss");
         filePath=QDir::homePath();//QFileDialog::getExistingDirectory(this,"");

         savePath=QString("%1/%2.jpg").arg(filePath).arg(saveName);
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

    Laplace(ho_Image, &ho_ImageLaplace, "absolute", 3, "n_4");
    ho_Image=ho_ImageLaplace;

    fileName=QString("%1_%2").arg(middlePictureName).arg(middlePictureId);
    savePath=QString("%1/%2.jpg").arg(middleSavePath).arg(fileName);
    WriteImage(ho_Image, "jpeg", 0, HTuple(savePath.toStdString().c_str()));
    showPicture(ui,savePath);//图片名字前得带上路径
    ui->label->setText(savePath);
    middlePictureId++;

}

void PreTreat::on_pushButton_clicked()
{
    InvertImage(ho_Image, &ho_ImageInvert);  //反色处理
    ho_Image=ho_ImageInvert;                //传递

    fileName=QString("%1_%2").arg(middlePictureName).arg(middlePictureId);
    savePath=QString("%1/%2.jpg").arg(middleSavePath).arg(fileName);
    WriteImage(ho_Image, "jpeg", 0, HTuple(savePath.toStdString().c_str()));
    showPicture(ui,savePath);//图片名字前得带上路径
    ui->label->setText(savePath);

    middlePictureId++;
}

void PreTreat::on_SobelButton_clicked()
{

    SobelAmp(ho_Image, &ho_EdgeAmplitude, "sum_abs", 3); //sobel处理
    ho_Image=ho_EdgeAmplitude;                //传递

    fileName=QString("%1_%2").arg(middlePictureName).arg(middlePictureId);
    savePath=QString("%1/%2.jpg").arg(middleSavePath).arg(fileName);
    WriteImage(ho_Image, "jpeg", 0, HTuple(savePath.toStdString().c_str()));
    showPicture(ui,savePath);//图片名字前得带上路径
    ui->label->setText(savePath);
    middlePictureId++;
}

void PreTreat::on_SmoothButton_clicked()
{

   SmoothImage(ho_Image, &ho_ImageSmooth, "gauss", 5);//平滑
    ho_Image=ho_ImageSmooth;                //传递

    fileName=QString("%1_%2").arg(middlePictureName).arg(middlePictureId);
    savePath=QString("%1/%2.jpg").arg(middleSavePath).arg(fileName);
    WriteImage(ho_Image, "jpeg", 0, HTuple(savePath.toStdString().c_str()));
    showPicture(ui,savePath);//图片名字前得带上路径
    ui->label->setText(savePath);
    middlePictureId++;
}

void PreTreat::on_ErosionButton_clicked()
{

    GenDiscSe(&ho_SE, "byte", 8, 8, 0);
     GrayErosion(ho_Image, ho_SE, &ho_ImageErosion);//腐蚀
     ho_Image=ho_ImageErosion;                //传递

     fileName=QString("%1_%2").arg(middlePictureName).arg(middlePictureId);
     savePath=QString("%1/%2.jpg").arg(middleSavePath).arg(fileName);
     WriteImage(ho_Image, "jpeg", 0, HTuple(savePath.toStdString().c_str()));
     showPicture(ui,savePath);//图片名字前得带上路径
     ui->label->setText(savePath);
     middlePictureId++;
}


void PreTreat::on_DilationButton_clicked()
{

    GenDiscSe(&ho_SE, "byte", 8, 8, 0);
     GrayDilation(ho_Image, ho_SE, &ho_ImageDilation);//腐蚀
     ho_Image=ho_ImageDilation;                //传递

     fileName=QString("%1_%2").arg(middlePictureName).arg(middlePictureId);
     savePath=QString("%1/%2.jpg").arg(middleSavePath).arg(fileName);
     WriteImage(ho_Image, "jpeg", 0, HTuple(savePath.toStdString().c_str()));
     showPicture(ui,savePath);//图片名字前得带上路径
     ui->label->setText(savePath);
     middlePictureId++;
}

void PreTreat::on_HighpassButton_clicked()
{

    GenDiscSe(&ho_SE, "byte", 8, 8, 0);
     HighpassImage(ho_Image, &ho_Highpass, 19, 19);
     ho_Image=ho_Highpass;                //传递

     fileName=QString("%1_%2").arg(middlePictureName).arg(middlePictureId);
     savePath=QString("%1/%2.jpg").arg(middleSavePath).arg(fileName);
     WriteImage(ho_Image, "jpeg", 0, HTuple(savePath.toStdString().c_str()));
     showPicture(ui,savePath);//图片名字前得带上路径
     ui->label->setText(savePath);
     middlePictureId++;
}

void PreTreat::on_LowpassButton_clicked()
{

    GenDiscSe(&ho_SE, "byte", 8, 8, 0);
      MeanImage(ho_Image, &ho_ImageMean, 19, 19);
    ho_Image=  ho_ImageMean;              //传递

    fileName=QString("%1_%2").arg(middlePictureName).arg(middlePictureId);
    savePath=QString("%1/%2.jpg").arg(middleSavePath).arg(fileName);
    WriteImage(ho_Image, "jpeg", 0, HTuple(savePath.toStdString().c_str()));
    showPicture(ui,savePath);//图片名字前得带上路径
    ui->label->setText(savePath);
    middlePictureId++;
}

void PreTreat::on_MedianpassButton_clicked()
{

    GenDiscSe(&ho_SE, "byte", 8, 8, 0);
  MedianImage(ho_Image, &ho_ImageMedian, "circle", 3, "continued");
     ho_Image=  ho_ImageMedian;              //传递

     fileName=QString("%1_%2").arg(middlePictureName).arg(middlePictureId);
     savePath=QString("%1/%2.jpg").arg(middleSavePath).arg(fileName);
     WriteImage(ho_Image, "jpeg", 0, HTuple(savePath.toStdString().c_str()));
     showPicture(ui,savePath);//图片名字前得带上路径
     ui->label->setText(savePath);
     middlePictureId++;
}

int ThesholdInputDialog::getMaxGray()//这里用函数是为了调用ThesholdInputDialog里面的成员
{
    return ui->maxlineEdit->text().toInt();
}

int ThesholdInputDialog::getMinGray()
{
    return ui->minlineEdit->text().toInt();
}
int ThesholdInputDialog::getForegroundGray()
{
    return ui->ForegroundGraylineEdit->text().toInt();
}
int ThesholdInputDialog::getBackgroundGray()
{
    return ui->BackgroundGraylineEdit->text().toInt();
}
void PreTreat::on_thresholdButton_clicked()
{
    int mingray,maxgray;
    int ForegroundGray,BackgroundGray;
    tidialog = new ThesholdInputDialog(this);//实例化
    //tidialog->show(); //模态方法
    if (tidialog->exec() == QDialog::Accepted)
    {
        maxgray=tidialog->getMaxGray();
        mingray=tidialog->getMinGray();
        ForegroundGray=tidialog->getForegroundGray();
        BackgroundGray=tidialog->getBackgroundGray();
    }


    Threshold(ho_Image, &ho_Region, mingray, maxgray);//阈值分割
    Connection(ho_Region, &ho_ConnectedRegions);//好像没什么用？
    //RegionToMean(ho_Region,ho_Image,&ho_RegionImage);//使用均值来填充图像区域并转化为image
    RegionToBin(ho_ConnectedRegions,&ho_RegionImage,ForegroundGray,BackgroundGray,hv_Width,hv_Height);
    //将图像与区域转化成一个二进制字节图像。给区域内的所有像素赋予前景灰度值，区域外则赋予后景灰度值
    ho_Image = ho_RegionImage;

    fileName=QString("%1_%2").arg(middlePictureName).arg(middlePictureId);
    savePath=QString("%1/%2.jpg").arg(middleSavePath).arg(fileName);
    WriteImage(ho_Image, "jpeg", 0, HTuple(savePath.toStdString().c_str()));
    showPicture(ui,savePath);//图片名字前得带上路径
    ui->label->setText(savePath);
    middlePictureId++;
}
