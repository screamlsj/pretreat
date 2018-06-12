#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <X11/Xlib.h>

#include "HalconCpp.h"
#include "HDevThread.h"

QString filePathName;
QLabel *info_label;
QLabel *size_label;
QLabel *posInfo_label;
QString type;
QImage *image;

HObject ho_Image;
HTuple hv_Width,hv_Height,hv_Type,hv_num_channels,hv_Grayval;
int hw,hh;
int globalMark;

double time_Start;
double time_End ;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    info_label=new QLabel("file info");
    ui->statusBar->addWidget(info_label);//将标签添加到状态栏
    size_label=new QLabel("size");
    ui->statusBar->addWidget(size_label);
    posInfo_label=new QLabel;
    ui->statusBar->addWidget(posInfo_label);
    globalMark=0;

    QFile *file;
    QString filename="sysconfig.xml";
    sysfile *sysf=new sysfile(this);
    if(!file->exists("sysconfig.xml"))
        sysf->create_sysfile(filename);
}

MainWindow::~MainWindow()
{
    delete ui;
}
//void rgb3_to_interleaved (HObject ho_ImageRGB, HObject *ho_ImageInterleaved);
//void rgb3_to_interleaved (HObject ho_ImageRGB, HObject *ho_ImageInterleaved)
//{

//  // Local iconic variables
//  HObject  ho_ImageAffineTrans, ho_ImageRed, ho_ImageGreen;
//  HObject  ho_ImageBlue, ho_RegionGrid, ho_RegionMoved, ho_RegionClipped;

//  // Local control variables
//  HTuple  hv_PointerRed, hv_PointerGreen, hv_PointerBlue;
//  HTuple  hv_Type, hv_Width, hv_Height, hv_HomMat2DIdentity;
//  HTuple  hv_HomMat2DScale;

//  GetImagePointer3(ho_ImageRGB, &hv_PointerRed, &hv_PointerGreen, &hv_PointerBlue,
//      &hv_Type, &hv_Width, &hv_Height);
//  GenImageConst(&(*ho_ImageInterleaved), "byte", hv_Width*3, hv_Height);
//  //
//  HomMat2dIdentity(&hv_HomMat2DIdentity);
//  HomMat2dScale(hv_HomMat2DIdentity, 1, 3, 0, 0, &hv_HomMat2DScale);
//  AffineTransImageSize(ho_ImageRGB, &ho_ImageAffineTrans, hv_HomMat2DScale, "constant",
//      hv_Width*3, hv_Height);
//  //
//  Decompose3(ho_ImageAffineTrans, &ho_ImageRed, &ho_ImageGreen, &ho_ImageBlue);
//  GenGridRegion(&ho_RegionGrid, 2*hv_Height, 3, "lines", hv_Width*3, hv_Height+1);
//  MoveRegion(ho_RegionGrid, &ho_RegionMoved, -1, 0);
//  ClipRegion(ho_RegionMoved, &ho_RegionClipped, 0, 0, hv_Height-1, (3*hv_Width)-1);
//  //NOTE: Due to internal limitations, the images ImageRed, ImageGreen, and ImageBlue
//  //cannot be displayed by HDevelop.Trying to display one of these images results in the
//  //error message 'Internal error: number of chords too big for num_max'. However, this
//  //affects by no means the continuation or the results of this example program, and
//  //therefore, is no reason to be alarmed !
//  ReduceDomain(ho_ImageRed, ho_RegionClipped, &ho_ImageRed);
//  MoveRegion(ho_RegionGrid, &ho_RegionMoved, -1, 1);
//  ClipRegion(ho_RegionMoved, &ho_RegionClipped, 0, 0, hv_Height-1, (3*hv_Width)-1);
//  ReduceDomain(ho_ImageGreen, ho_RegionClipped, &ho_ImageGreen);
//  MoveRegion(ho_RegionGrid, &ho_RegionMoved, -1, 2);
//  ClipRegion(ho_RegionMoved, &ho_RegionClipped, 0, 0, hv_Height-1, (3*hv_Width)-1);
//  ReduceDomain(ho_ImageBlue, ho_RegionClipped, &ho_ImageBlue);
//  OverpaintGray((*ho_ImageInterleaved), ho_ImageRed);
//  OverpaintGray((*ho_ImageInterleaved), ho_ImageGreen);
//  OverpaintGray((*ho_ImageInterleaved), ho_ImageBlue);
//  return;
//}
//void HObjectToQImage(HObject himage,QImage **qimage)
//{
//    HTuple hChannels;
//    HTuple   width,height;
//    width=height=0;
//    HTuple htype;
//    HTuple hpointer;

//    ConvertImageType(himage,&himage,"byte");//将图片转化成byte类型
//    CountChannels(himage,&hChannels);       //判断图像通道数


//    if(hChannels[0].I()==1)//单通道图
//    {
//        unsigned char *ptr;

//        GetImagePointer1(himage,&hpointer,&htype,&width,&height);

//        ptr=(unsigned char *)hpointer[0].L();
//        *(*qimage)=QImage(ptr,width,height,width,QImage::Format_Indexed8);//不知道是否已自动4字节对齐
//    }
//    else if(hChannels[0].I()==3)//三通道图
//    {
//        unsigned char *ptr3;

//        HObject ho_ImageInterleaved;
//        rgb3_to_interleaved(himage, &ho_ImageInterleaved);
//        GetImagePointer1(ho_ImageInterleaved, &hpointer, &htype, &width, &height);

//        ptr3=(unsigned char *)hpointer[0].L();
//        *(*qimage)=QImage(ptr3,width/3,height,width,QImage::Format_RGB888);
//    }
//    /*
//    else if(hChannels[0].I()==3)//三通道图
//    {
//        HTuple hv_ptrRed,hv_ptrGreen,hv_ptrBlue;
//        GetImagePointer3(himage,&hv_ptrRed,&hv_ptrGreen,&hv_ptrBlue,&htype,&width,&height);
//        uchar *ptrRed=(uchar*)hv_ptrRed[0].L();
//        uchar *ptrGreen=(uchar*)hv_ptrGreen[0].L();
//        uchar *ptrBlue=(uchar*)hv_ptrBlue[0].L();

//        int bytesperline=(width*8*3+31)/32*4;//针对位深为8的三通道图进行每行4字节对齐补齐
//        int bytecount=bytesperline*height;
//        uchar* data8=new uchar[bytecount];
//        int lineheadid,pixid;

// //time_Start = (double)clock();
//        for(int i=0;i<height;i++)
//        {
//            lineheadid=bytesperline*i;//计算出图像第i行的行首在图像数据中的地址
//            for(int j=0;j<width;j++)
//            {
//                pixid=lineheadid+j*3;//计算坐标为（i，j）的像素id
// //                data8[pixid]=ptrRed[width*i+j];
// //                data8[pixid+1]=ptrGreen[width*i+j];
// //                data8[pixid+2]=ptrBlue[width*i+j];
//                *(data8+pixid)=*(ptrRed+width*i+j);
//                *(data8+pixid+1)=*(ptrGreen+width*i+j);
//                *(data8+pixid+2)=*(ptrBlue+width*i+j);
//            }
//        }
// //        time_End = (double)clock();

//        *(*qimage)=QImage(data8,width,height,QImage::Format_RGB888);
//    }
//    */
//}

void MainWindow::showPicture(QImage *qimage)
{
    GetImageSize(ho_Image,&hv_Width,&hv_Height);
    GetImageType(ho_Image,&hv_Type);
    CountChannels(ho_Image, &hv_num_channels);
    hw=hv_Width.I();
    hh=hv_Height.I();
    type=hv_Type.ToString();
    size_label->setText(QString("%1x%2x%3 "+type).arg(hw).arg(hh).arg(hv_num_channels.I()));



    if(qimage!=NULL)
    {
                ui->display_label->setPixmap(QPixmap::fromImage(*qimage));
                ui->display_label->resize(hv_Width.I(),hv_Height.I());//如果改变框的大小，图像并不会有大小变化
               // ui->display_label->setAlignment(Qt::AlignCenter);
                globalMark=1;
    }

}

void MainWindow::on_openImage_action_triggered()//打开图像文件
{
    ShowImage showimage;
    filePathName = QFileDialog::getOpenFileName(this,tr("open image file"), "",
                                                tr("Image files(*.jpg *.png *.jpeg);;All files (*.*)"));
                                                        //窗口文字     目录为空可以打开上次目录       筛选后缀
    if(filePathName!=NULL)
    {

        info_label->setText(filePathName);

        ReadImage(&ho_Image, HTuple(filePathName.toStdString().c_str()));

        time_Start = (double)clock();



        image=new QImage;
        //HObjectToQImage(ho_Image,&image);

       showimage.HtoQimage(ho_Image,&image);

               time_End = (double)clock();

        showPicture(image);



        qDebug()<<(time_End - time_Start)/1000.0<<"s";
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    int x,y;
    QPoint qpos=event->globalPos();
    QPoint qpos1=ui->display_label->mapFromGlobal(qpos);
    x=qpos1.x();
    y=qpos1.y();
    if(globalMark==1 && 0<=x && x<hw && 0<=y && y<hh)
    {
      GetGrayval(ho_Image,y,x,&hv_Grayval);//注意行列容易搞错
      if(hv_num_channels.I()==1)
      {
          posInfo_label->setText(QString("mouse position:%1,%2  grayValue:%3")
                                 .arg(x).arg(y).arg(hv_Grayval.I()));   //默认r通道灰度值，g和b分别存在[1]和[2]中
      }
      else if(hv_num_channels.I()==3)
      {
          posInfo_label->setText(QString("mouse position:%1,%2  grayValue:r=%3 g=%4 b=%5").arg(x).arg(y)
                                 .arg(hv_Grayval[0].I()).arg(hv_Grayval[1].I()).arg(hv_Grayval[2].I()));
      }

    }


}

void MainWindow::on_pretreat_pushButton_clicked()
{

    if(globalMark==1)
    {
        prtredialog=new PreTreatDialog(this);
        PreTreatDialog::previewImage=ho_Image;
               if(prtredialog->exec()==QDialog::Accepted)
               {
                   prtredialog->saveDefaultPara();

                   ho_Image=PreTreatDialog::previewImage;
                   CountChannels(ho_Image, &hv_num_channels);
                   ShowImage showimage;
                   image=new QImage;
                  showimage.HtoQimage(ho_Image,&image);
                   showPicture(image);
               }
    }
    else
    {
        QMessageBox::information(this,"information","no image to treat");
    }
}

void MainWindow::on_dopretreat_pushButton_clicked()
{

    prtredialog=new PreTreatDialog(this);

    prtredialog->pretreatImage(&ho_Image);

    CountChannels(ho_Image, &hv_num_channels);
    ShowImage showimage;
    image=new QImage;
   showimage.HtoQimage(ho_Image,&image);
    showPicture(image);
}
