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
HObject ho_ImageScaled;
HObject  ho_Red, ho_Green, ho_Blue;
HObject ho_ImageInterleaved;
HTuple  hv_Pointer, hv_Width, hv_Height,hv_Type;
HObject  ho_ImageAffineTrans, ho_RegionAffineTrans;
HTuple  hv_HomMat2DIdentity;
HTuple  hv_HomMat2DRotate, hv_HomMat2DScale;
HObject ho_Image2;
HTuple hv_Width2,hv_Height2;
HObject  ho_ImagePart,ho_ImagePart1,ho_ImagePart2, ho_ImageResult;
HObject ho_ImageEmphasize;
HObject ho_ImageScaleMax;
HObject ho_ImageIlluminate;

QString filePath;
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
    filePath=QDir::currentPath();
    fileName = QFileDialog::getOpenFileName(this,tr("open image file"), "", tr("Image files(*.jpg *.png *.jpeg);;All files (*.*)"));
                                                        //窗口文字     目录为空可以打开上次目录       筛选后缀
    if(fileName!="")
    {
        ReadImage(&ho_Image, HTuple(fileName.toStdString().c_str()));
        GetImageSize(ho_Image,&hv_Width,&hv_Height);
        GetImageType(ho_Image,&hv_Type);
        showPicture(ui,fileName);
        ui->label->setText(fileName);
        ui->label_2->setText(QString("w:%1 h:%2 type:%3").arg(int(hv_Width)).arg(int(hv_Height)) );
        ui->label_3->setText(QString(hv_Type.ToString()));
        //globalMark部分待添加
        globalMark=1;
        middlePictureId=1;
    }
}

void PreTreat::on_SaveImageButton_clicked()//保存图像文件
{
    if(globalMark==1)
    {
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

    if(globalMark==1)
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
    else
    {
        QMessageBox::information(this,"Message","no image to treat");
    }
}

void PreTreat::on_pushButton_clicked()
{
    if(globalMark==1)
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
    else
    {
        QMessageBox::information(this,"Message","no image to treat");
    }
}

void PreTreat::on_SobelButton_clicked()
{
    if(globalMark==1)
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
    else
    {
        QMessageBox::information(this,"Message","no image to treat");
    }
}

void PreTreat::on_SmoothButton_clicked()
{
    if(globalMark==1)
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
    else
    {
        QMessageBox::information(this,"Message","no image to treat");
    }
}

void PreTreat::on_ErosionButton_clicked()
{
    if(globalMark==1)
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
    else
    {
        QMessageBox::information(this,"Message","no image to treat");
    }
}


void PreTreat::on_DilationButton_clicked()
{
    if(globalMark==1)
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
    else
    {
        QMessageBox::information(this,"Message","no image to treat");
    }
}

void PreTreat::on_HighpassButton_clicked()
{
    if(globalMark==1)
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
    else
    {
        QMessageBox::information(this,"Message","no image to treat");
    }

}

void PreTreat::on_LowpassButton_clicked()
{
    if(globalMark==1)
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
    else
    {
        QMessageBox::information(this,"Message","no image to treat");
    }

}

void PreTreat::on_MedianpassButton_clicked()
{
    if(globalMark==1)
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
    else
    {
        QMessageBox::information(this,"Message","no image to treat");
    }

}

//threshold阈值分割二指化模块
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
    if(globalMark==1)
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
    }
    else
    {
        QMessageBox::information(this,"Message","no image to treat");
    }

}

//亮度调节模块
double ScaleInputDialog::getMultValue()
{
    return ui->MultlineEdit->text().toDouble();
}
int ScaleInputDialog::getAddValue()
{
    return ui->AddlineEdit->text().toInt();
}
void PreTreat::on_ScaleButton_clicked()
{
    if(globalMark==1)
    {
        double multvalue;
        int addvalue;
        sidialog = new ScaleInputDialog(this);
        if(sidialog->exec()==QDialog::Accepted)
        {
              multvalue=sidialog->getMultValue();
              addvalue=sidialog->getAddValue();
              ScaleImage(ho_Image, &ho_ImageScaled, multvalue,addvalue);
              ho_Image=ho_ImageScaled;

              fileName=QString("%1_%2").arg(middlePictureName).arg(middlePictureId);
              savePath=QString("%1/%2.jpg").arg(middleSavePath).arg(fileName);
              WriteImage(ho_Image, "jpeg", 0, HTuple(savePath.toStdString().c_str()));
              showPicture(ui,savePath);//图片名字前得带上路径
              ui->label->setText(savePath);
              middlePictureId++;
        }
    }
    else
    {
        QMessageBox::information(this,"Message","no image to treat");
    }

}

//通道分解模块
int DecomposeDialog::getChoice()
{
    return ui->comboBox->currentIndex();
}
void PreTreat::on_DecomposeButton_clicked()
{
    if(globalMark==1)
    {
        dcDialog = new DecomposeDialog(this);//得先实例化，很重要
        if(dcDialog->exec()==QDialog::Accepted)
        {
            int choice;
            choice=dcDialog->getChoice();
            Decompose3(ho_Image,&ho_Red,&ho_Green,&ho_Blue);
            if(choice==0)
            {
                ho_Image=ho_Red;
            }
            else if(choice==1)
            {
                ho_Image=ho_Green;
            }
            else if(choice==2)
            {
                ho_Image=ho_Blue;
            }

            fileName=QString("%1_%2").arg(middlePictureName).arg(middlePictureId);
            savePath=QString("%1/%2.jpg").arg(middleSavePath).arg(fileName);
            WriteImage(ho_Image, "jpeg", 0, HTuple(savePath.toStdString().c_str()));
            showPicture(ui,savePath);//图片名字前得带上路径
            ui->label->setText(savePath);
            middlePictureId++;
        }
    }
    else
    {
        QMessageBox::information(this,"Message","no image to treat");
    }

}

//几何变换模块
void rgb3_to_interleaved (HObject ho_ImageRGB, HObject *ho_ImageInterleaved);
void rgb3_to_interleaved (HObject ho_ImageRGB, HObject *ho_ImageInterleaved)
{

  // Local iconic variables
  HObject  ho_ImageAffineTrans, ho_ImageRed, ho_ImageGreen;
  HObject  ho_ImageBlue, ho_RegionGrid, ho_RegionMoved, ho_RegionClipped;

  // Local control variables
  HTuple  hv_PointerRed, hv_PointerGreen, hv_PointerBlue;
  HTuple  hv_Type, hv_Width, hv_Height, hv_HomMat2DIdentity;
  HTuple  hv_HomMat2DScale;

  GetImagePointer3(ho_ImageRGB, &hv_PointerRed, &hv_PointerGreen, &hv_PointerBlue,
      &hv_Type, &hv_Width, &hv_Height);
  GenImageConst(&(*ho_ImageInterleaved), "byte", hv_Width*3, hv_Height);
  //
  HomMat2dIdentity(&hv_HomMat2DIdentity);
  HomMat2dScale(hv_HomMat2DIdentity, 1, 3, 0, 0, &hv_HomMat2DScale);
  AffineTransImageSize(ho_ImageRGB, &ho_ImageAffineTrans, hv_HomMat2DScale, "constant",
      hv_Width*3, hv_Height);
  //
  Decompose3(ho_ImageAffineTrans, &ho_ImageRed, &ho_ImageGreen, &ho_ImageBlue);
  GenGridRegion(&ho_RegionGrid, 2*hv_Height, 3, "lines", hv_Width*3, hv_Height+1);
  MoveRegion(ho_RegionGrid, &ho_RegionMoved, -1, 0);
  ClipRegion(ho_RegionMoved, &ho_RegionClipped, 0, 0, hv_Height-1, (3*hv_Width)-1);
  //NOTE: Due to internal limitations, the images ImageRed, ImageGreen, and ImageBlue
  //cannot be displayed by HDevelop.Trying to display one of these images results in the
  //error message 'Internal error: number of chords too big for num_max'. However, this
  //affects by no means the continuation or the results of this example program, and
  //therefore, is no reason to be alarmed !
  ReduceDomain(ho_ImageRed, ho_RegionClipped, &ho_ImageRed);
  MoveRegion(ho_RegionGrid, &ho_RegionMoved, -1, 1);
  ClipRegion(ho_RegionMoved, &ho_RegionClipped, 0, 0, hv_Height-1, (3*hv_Width)-1);
  ReduceDomain(ho_ImageGreen, ho_RegionClipped, &ho_ImageGreen);
  MoveRegion(ho_RegionGrid, &ho_RegionMoved, -1, 2);
  ClipRegion(ho_RegionMoved, &ho_RegionClipped, 0, 0, hv_Height-1, (3*hv_Width)-1);
  ReduceDomain(ho_ImageBlue, ho_RegionClipped, &ho_ImageBlue);
  OverpaintGray((*ho_ImageInterleaved), ho_ImageRed);
  OverpaintGray((*ho_ImageInterleaved), ho_ImageGreen);
  OverpaintGray((*ho_ImageInterleaved), ho_ImageBlue);
  return;
}
void GeometricTransDialog::getcutIndex(int *x,int *y,int *w,int *h)
{
    (*x)=ui->x_lineEdit->text().toInt();
    (*y)=ui->y_lineEdit->text().toInt();
    (*w)=ui->w_lineEdit_2->text().toInt();
    (*h)=ui->h_lineEdit->text().toInt();
}
void PreTreat::on_GeoTransButton_clicked()
{
    if(globalMark==1)
    {
        gtdialog = new GeometricTransDialog(this);
        if(gtdialog->exec()==QDialog::Accepted)
        {
//              rgb3_to_interleaved(ho_Image, &ho_ImageInterleaved);
//              GetImagePointer1(ho_ImageInterleaved, &hv_Pointer, &hv_TypeRGB, &hv_Width, &hv_Height);
//              GenImageInterleaved(&ho_Image, hv_Pointer, "rgb", hv_Width/3, hv_Height, -1,
//                  "byte", hv_Width/6, hv_Height/2, 0, hv_Width/12, -1, 0);

              int x,y,w,h;
              gtdialog->getcutIndex(&x,&y,&w,&h);

              CropPart(ho_Image, &ho_ImagePart, y, x, w,h);
              ho_Image=ho_ImagePart;

              //输入图像大小，
              fileName=QString("%1_%2").arg(middlePictureName).arg(middlePictureId);
              savePath=QString("%1/%2.jpg").arg(middleSavePath).arg(fileName);
              WriteImage(ho_Image, "jpeg", 0, HTuple(savePath.toStdString().c_str()));
              showPicture(ui,savePath);//图片名字前得带上路径
              ui->label->setText(savePath);
              middlePictureId++;
        }
    }
    else
    {
        QMessageBox::information(this,"information","no image to treat");
    }
}

//仿射变换模块
void AffineTransDialog::getAffineIndex(float *phi, int *w1, int *h1, float *scale_x, float *scale_y, int *w2, int *h2)
{
    (*phi)=ui->phi_lineEdit->text().toFloat();
    (*w1)=ui->w1_lineEdit->text().toInt();
    (*h1)=ui->h1_lineEdit->text().toInt();
    (*scale_x)=ui->scale_x_lineEdit->text().toFloat();
    (*scale_y)=ui->scale_y_lineEdit->text().toFloat();
    (*w2)=ui->w2_lineEdit->text().toInt();
    (*h2)=ui->h2_lineEdit->text().toInt();
}
void PreTreat::on_affineTranspushButton_clicked()
{
    if(globalMark==1)
    {
        aftdialog = new AffineTransDialog(this);
        if(aftdialog->exec()==QDialog::Accepted)
        {
            int w1,h1,w2,h2;
            float phi,scale_x,scale_y;
            aftdialog->getAffineIndex(&phi,&w1,&h1,&scale_x,&scale_y,&w2,&h2);

            HomMat2dIdentity(&hv_HomMat2DIdentity);//产生仿射变换矩阵
            //需改进：坐标还是需要从图像获取
            HomMat2dRotate(hv_HomMat2DIdentity, ((HTuple)phi).TupleRad(), w1, h1, &hv_HomMat2DRotate);
            //把旋转角度添加到仿射变换矩阵
            HomMat2dScale(hv_HomMat2DRotate, scale_x,scale_y, w2, h2, &hv_HomMat2DScale);
            //把缩放添加到仿射变换矩阵
            AffineTransImage(ho_Image, &ho_ImageAffineTrans, hv_HomMat2DScale, "nearest_neighbor","false");

            ho_Image=ho_ImageAffineTrans;

            fileName=QString("%1_%2").arg(middlePictureName).arg(middlePictureId);
            savePath=QString("%1/%2.jpg").arg(middleSavePath).arg(fileName);
            WriteImage(ho_Image, "jpeg", 0, HTuple(savePath.toStdString().c_str()));
            showPicture(ui,savePath);//图片名字前得带上路径
            ui->label->setText(savePath);
            middlePictureId++;
        }
    }
    else
    {
        QMessageBox::information(this,"information","no image to treat");
    }
}


//图像比较模块
void CompareDialog::getCompareInform(QString *fileName2,int *operation)
{
    (*fileName2)=ui->label->text();
    (*operation)=ui->comboBox->currentIndex();
}
void PreTreat::on_CompareButton_clicked()
{
    if(globalMark==1)
    {
        cpdialog = new CompareDialog(this);
        int operation;
        if(cpdialog->exec()==QDialog::Accepted)
        {
            cpdialog->getCompareInform(&fileName,&operation);
            //ui->label->setText(fileName);
            if(fileName!="")
            {
                ReadImage(&ho_Image2, HTuple(fileName.toStdString().c_str()));
                GetImageSize(ho_Image2,&hv_Width2,&hv_Height2);
                GetImageSize(ho_Image,&hv_Width,&hv_Height);

                showPicture(ui,fileName);
                ui->label->setText(fileName);

                HTuple min_width,min_height;//以最小的图片大小为准
                if(hv_Width>hv_Width2)
                {
                    min_width=hv_Width2;
                }
                else
                {
                    min_width=hv_Width;
                }
                if(hv_Height>hv_Height2)
                {
                    min_height=hv_Height2;
                }
                else
                {
                    min_height=hv_Height;
                }

                CropPart(ho_Image, &ho_ImagePart1, 0, 0, min_width, min_height);
                CropPart(ho_Image2, &ho_ImagePart2, 0, 0, min_width,min_height);
            }
            if(operation==0)//图像相加
            {
                AddImage(ho_ImagePart1, ho_ImagePart2, &ho_ImageResult, 0.5, 0);
            }
            else if(operation==1)//图像相减
            {
                SubImage(ho_ImagePart1, ho_ImagePart2, &ho_ImageResult, 1, 50);
            }
            else if(operation==2)//图像相减，所选图片作为被减图
            {
                SubImage(ho_ImagePart2, ho_ImagePart1, &ho_ImageResult, 1, 50);

            }
            else if(operation ==3)//min
            {
                  MinImage(ho_ImagePart1, ho_ImagePart2, &ho_ImageResult);
            }
            else if(operation==4)//max
            {
                  MaxImage(ho_ImagePart1, ho_ImagePart2, &ho_ImageResult);
            }

            ho_Image=ho_ImageResult;

            fileName=QString("%1_%2").arg(middlePictureName).arg(middlePictureId);
            savePath=QString("%1/%2.jpg").arg(middleSavePath).arg(fileName);
            WriteImage(ho_Image, "jpeg", 0, HTuple(savePath.toStdString().c_str()));
            showPicture(ui,savePath);//图片名字前得带上路径
            ui->label->setText(savePath);
            middlePictureId++;
        }
    }
    else
    {
        QMessageBox::information(this,"information","no image to treat");
    }

}

//图像增强模块
void EmphasizeDialog::getEmphasizeIndex(int *mask,float *factor)
{
    (*mask)=ui->mask_lineEdit->text().toInt();
    (*factor)=ui->factor_lineEdit->text().toFloat();
}

void PreTreat::on_EmphasizeButton_clicked()
{
    if(globalMark==1)
    {
        epdialog =new EmphasizeDialog(this);
        if(epdialog->exec()==QDialog::Accepted)
        {
            int mask;
            float factor;
            epdialog->getEmphasizeIndex(&mask,&factor);
            Emphasize(ho_Image,&ho_ImageEmphasize,mask,mask,factor);
            ho_Image=ho_ImageEmphasize;

            fileName=QString("%1_%2").arg(middlePictureName).arg(middlePictureId);
            savePath=QString("%1/%2.jpg").arg(middleSavePath).arg(fileName);
            WriteImage(ho_Image, "jpeg", 0, HTuple(savePath.toStdString().c_str()));
            showPicture(ui,savePath);//图片名字前得带上路径
            ui->label->setText(savePath);
            middlePictureId++;
        }
    }
    else
    {
        QMessageBox::information(this,"information","no image to treat");
    }
}

//灰度直方图均衡化
int ScaleMaxDialog::getScaleMaxChoice()
{
    if(ui->radioButton->isChecked())
    {
        return 1;
    }
    else if(ui->radioButton_2->isChecked())
    {
        return 2;
    }
    return 0;
}
void PreTreat::on_scale_max_pushButton_clicked()
{
    if(globalMark==1)
    {
        smdialog =new ScaleMaxDialog(this);
        if(smdialog->exec()==QDialog::Accepted)
        {
            int signal;
            signal=smdialog->getScaleMaxChoice();
            if(signal==1)
            {
                ScaleImageMax(ho_Image, &ho_ImageScaleMax);
            }
            else if(signal==2)
            {
                EquHistoImage(ho_Image, &ho_ImageScaleMax);
            }
            else if(signal==0)
            {
                QMessageBox::information(this,"information","error: signal==0");
            }
            ho_Image=ho_ImageScaleMax;

            fileName=QString("%1_%2").arg(middlePictureName).arg(middlePictureId);
            savePath=QString("%1/%2.jpg").arg(middleSavePath).arg(fileName);
            WriteImage(ho_Image, "jpeg", 0, HTuple(savePath.toStdString().c_str()));
            showPicture(ui,savePath);//图片名字前得带上路径
            ui->label->setText(savePath);
            middlePictureId++;
        }
    }
    else
    {
        QMessageBox::information(this,"information","no image to treat");
    }
}

//亮度改善
void IlluminateDialog::getIlluminateIndex(int *mask,float *factor)
{
    (*mask)=ui->lineEdit->text().toInt();
    (*factor)=ui->lineEdit_2->text().toFloat();
}
void PreTreat::on_illuminatepushButton_clicked()
{
    if(globalMark==1)
    {
        ildialog =new IlluminateDialog();
        if(ildialog->exec()==QDialog::Accepted)
        {
            int mask;
            float factor;
            ildialog->getIlluminateIndex(&mask,&factor);
            Illuminate(ho_Image, &ho_ImageIlluminate, mask, mask, factor);
            ho_Image=ho_ImageIlluminate;

            fileName=QString("%1_%2").arg(middlePictureName).arg(middlePictureId);
            savePath=QString("%1/%2.jpg").arg(middleSavePath).arg(fileName);
            WriteImage(ho_Image, "jpeg", 0, HTuple(savePath.toStdString().c_str()));
            showPicture(ui,savePath);//图片名字前得带上路径
            ui->label->setText(savePath);
            middlePictureId++;
        }
    }
    else
    {
        QMessageBox::information(this,"information","no image to treat");
    }

}
























