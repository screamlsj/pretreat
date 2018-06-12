#include "pretreatdialog.h"
#include "ui_pretreatdialog.h"

extern HObject ho_Image;
int mingray,maxgray;
int dual_minsize,dual_mingray,dual_threshold;
int var_masksize,var_absThreshold;
float var_stdDevScale;

int var_lightDark;

ShowImage showimage;
HObject PreTreatDialog::previewImage;

PreTreatDialog::PreTreatDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreTreatDialog)
{
    ui->setupUi(this);

    initSelectwidget();


    QImage *image=new QImage;
    showimage.HtoQimage(ho_Image,&image);
    showPicture(image);
}
PreTreatDialog::~PreTreatDialog()
{
    delete ui;
}

void PreTreatDialog::initSelectwidget()
{
    this->m_selectScrollArea = new QScrollArea(this);
  // this->m_selectScrollArea->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
  this->m_selectScrollArea->setWidgetResizable(true);//使内容长度可改变

    this->m_VLayout = new QVBoxLayout(this);
   // this->m_VLayout->setSizeConstraint(QVBoxLayout::SetMinAndMaxSize);

    QWidget* widget = new QWidget(this);

    //亮度调节 部件框
    scaleimage_presetwidget=new PretreatSetWidget;
    scaleimage_presetwidget->checkbox->setText("亮度调节");
    scaleimagewidget=new scaleimage_widget;
    scaleimage_presetwidget->setparawidgetlayout->addWidget(scaleimagewidget);
    this->m_VLayout->addWidget(scaleimage_presetwidget);

    //亮度改善 部件框
    illuminate_presetwidget=new PretreatSetWidget;
    illuminate_presetwidget->checkbox->setText("亮度改善");
    illuminatewidget=new illuminate_widget;
    illuminate_presetwidget->setparawidgetlayout->addWidget(illuminatewidget);
    this->m_VLayout->addWidget(illuminate_presetwidget);

    //模糊 部件框
    mean_presetwidget=new PretreatSetWidget;
    mean_presetwidget->checkbox->setText("模糊");
    meanwidget=new mean_widget;
    mean_presetwidget->setparawidgetlayout->addWidget(meanwidget);
    this->m_VLayout->addWidget(mean_presetwidget);

    //锐化 部件框
    emphasize_presetwidget=new PretreatSetWidget;
    emphasize_presetwidget->checkbox->setText("锐化");
    emphasizewidget=new emphasize_widget;
    emphasize_presetwidget->setparawidgetlayout->addWidget(emphasizewidget);
    this->m_VLayout->addWidget(emphasize_presetwidget);

    //中值滤波 部件框
    median_presetwidget=new PretreatSetWidget;
    median_presetwidget->checkbox->setText("中值滤波");

    medianwidget=new median_widget;
    median_presetwidget->setparawidgetlayout->addWidget(medianwidget);
    this->m_VLayout->addWidget(median_presetwidget);

    //通道分解 部件框
    decompose_presetwidget=new PretreatSetWidget;
    decompose_presetwidget->checkbox->setText("rgb通道分解");
    decomposewidget=new decompose_widget;
    decompose_presetwidget->setparawidgetlayout->addWidget(decomposewidget);
    this->m_VLayout->addWidget(decompose_presetwidget);

    //threshold 的部件框
    threshold_presetwidget=new PretreatSetWidget;
    threshold_presetwidget->checkbox->setText("threshold");
    thresholdwidget=new threshold_widget;
    threshold_presetwidget->setparawidgetlayout->addWidget(thresholdwidget);
    this->m_VLayout->addWidget(threshold_presetwidget);

    //腐蚀    部件框
    erosion_presetwidget=new PretreatSetWidget;
    erosion_presetwidget->checkbox->setText("腐蚀");
    erosionwidget=new erosionanddilation_widget;
    erosion_presetwidget->setparawidgetlayout->addWidget(erosionwidget);
    this->m_VLayout->addWidget(erosion_presetwidget);

    //膨胀    部件框
    dilation_presetwidget=new PretreatSetWidget;
    dilation_presetwidget->checkbox->setText("膨胀");
    dilationwidget=new erosionanddilation_widget;
    dilation_presetwidget->setparawidgetlayout->addWidget(dilationwidget);
    this->m_VLayout->addWidget(dilation_presetwidget);

    //开运算 部件框
    opening_presetwidget=new PretreatSetWidget;
    opening_presetwidget->checkbox->setText("开运算");
    openingwidget=new erosionanddilation_widget;
    opening_presetwidget->setparawidgetlayout->addWidget(openingwidget);
    this->m_VLayout->addWidget(opening_presetwidget);

    //闭运算 部件框
    closing_presetwidget=new PretreatSetWidget;
    closing_presetwidget->checkbox->setText("闭运算");
    closingwidget=new erosionanddilation_widget;
    closing_presetwidget->setparawidgetlayout->addWidget(closingwidget);
    this->m_VLayout->addWidget(closing_presetwidget);

//    int i = 0;
//    QString str("ckbox %1");
//    for (i=0; i<8; ++i)
//    {
//          presetwidget=new PretreatSetWidget;
//          presetwidget->checkbox->setText(str.arg(i));
//         //presetwidget->setparawidget->setVisible(false);
//          //presetwidget->setVisible(false);
//          //presetwidget->setMinimumSize(presetwidget->size());

//          label=new QLabel(presetwidget->setparawidget);
//          label->setText("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\nbbbbbb");

// //          testbutton=new QPushButton;
// //          testbutton->setText("ttttttttttt");
// //          presetwidget->setparawidgetlayout->addWidget(testbutton);

//          this->m_VLayout->addWidget(presetwidget);
//    }

    QWidget *emptywidget=new QWidget;
    m_VLayout->addWidget(emptywidget);

    widget->setLayout(this->m_VLayout);
    this->m_VLayout->setContentsMargins(0,0,0,0);
    this->m_VLayout->setSpacing(0);

    this->m_selectScrollArea->setWidget(widget);


    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(this->m_selectScrollArea);
    //this->setLayout(mainLayout);

    ui->selectwidget->setLayout(mainLayout);
    this->setDefaultPara();
}

void PreTreatDialog::showPicture(QImage *qimage)
{
    if(qimage!=NULL)
    {
       // *qimage=qimage->scaledToWidth(ui->previewlabel->size().width());//不能显示二值图？
        ui->previewlabel->setScaledContents(true);
        ui->previewlabel->setPixmap(QPixmap::fromImage(*qimage));
    }
}

void PreTreatDialog::setDefaultPara()
{
    sysfile *sysf=new sysfile(this);

    //scale
     scaleimage_presetwidget->checkbox->setChecked(sysf->load_sysparam((char*)"Pretreat",(char*)"Scale",(char*)"IsChecked","").toInt());
     scaleimagewidget->scaleimage_mult_lineedit->setText(sysf->load_sysparam((char*)"Pretreat",(char*)"Scale",(char*)"Mult",""));
     scaleimagewidget->scaleimage_add_spinbox->setValue(sysf->load_sysparam((char*)"Pretreat",(char*)"Scale",(char*)"Add","").toInt());
     //illuminate
    illuminate_presetwidget->checkbox->setChecked(sysf->load_sysparam((char*)"Pretreat",(char*)"Illuminate",(char*)"IsChecked","").toInt());
    illuminatewidget->illuminate_factor_combobox->setCurrentIndex(sysf->load_sysparam((char*)"Pretreat",(char*)"Illuminate",(char*)"Factor","").toInt());
    illuminatewidget->illuminate_masksize_combobox->setCurrentIndex(sysf->load_sysparam((char*)"Pretreat",(char*)"Illuminate",(char*)"MaskSize","").toInt());
    //mean
    mean_presetwidget->checkbox->setChecked(sysf->load_sysparam((char*)"Pretreat",(char*)"Mean",(char*)"IsChecked","").toInt());
    meanwidget->mean_masksize_combobox->setCurrentIndex(sysf->load_sysparam((char*)"Pretreat",(char*)"Mean",(char*)"MaskSize","").toInt());
    //emphasize
    emphasize_presetwidget->checkbox->setChecked(sysf->load_sysparam((char*)"Pretreat",(char*)"Emphasize",(char*)"IsChecked","").toInt());
    emphasizewidget->emphasize_factor_combobox->setCurrentIndex(sysf->load_sysparam((char*)"Pretreat",(char*)"Emphasize",(char*)"Factor","").toInt());
    emphasizewidget->emphasize_masksize_combobox->setCurrentIndex(sysf->load_sysparam((char*)"Pretreat",(char*)"Emphasize",(char*)"MaskSize","").toInt());
    //median
    median_presetwidget->checkbox->setChecked(sysf->load_sysparam((char*)"Pretreat",(char*)"Median",(char*)"IsChecked","").toInt());
    medianwidget->median_margin_combobox->setCurrentIndex(sysf->load_sysparam((char*)"Pretreat",(char*)"Median",(char*)"Margin","").toInt());
    medianwidget->median_masktype_combobox->setCurrentIndex(sysf->load_sysparam((char*)"Pretreat",(char*)"Median",(char*)"MaskType","").toInt());
    medianwidget->median_radius_combobox->setCurrentIndex(sysf->load_sysparam((char*)"Pretreat",(char*)"Median",(char*)"Radius","").toInt());
    //decompose
    decompose_presetwidget->checkbox->setChecked(sysf->load_sysparam((char*)"Pretreat",(char*)"Decompose",(char*)"IsChecked","").toInt());
    decomposewidget->decompose_combobox->setCurrentIndex(sysf->load_sysparam((char*)"Pretreat",(char*)"Decompose",(char*)"Choice","").toInt());
    //Threshold
    threshold_presetwidget->checkbox->setChecked(sysf->load_sysparam((char*)"Pretreat",(char*)"Threshold",(char*)"IsChecked","").toInt());
    thresholdwidget->combobox->setCurrentIndex(sysf->load_sysparam((char*)"Pretreat",(char*)"Threshold",(char*)"Choice","").toInt());
    thresholdwidget->mingray_spinBox->setValue(sysf->load_sysparam((char*)"Pretreat", (char*)"Threshold", (char*)"MinGray","").toInt());
    thresholdwidget->maxgray_spinBox->setValue(sysf->load_sysparam((char*)"Pretreat", (char*)"Threshold", (char*)"MaxGray","").toInt());
    thresholdwidget->dual_mingray_spinBox->setValue(sysf->load_sysparam((char*)"Pretreat", (char*)"Threshold", (char*)"DualMingray","").toInt());
    thresholdwidget->dual_minsize_lineedit->setText(sysf->load_sysparam((char*)"Pretreat", (char*)"Threshold", (char*)"DualMinsize",""));
    thresholdwidget->dual_threshold_spinBox->setValue(sysf->load_sysparam((char*)"Pretreat", (char*)"Threshold", (char*)"DualThreshold","").toInt());
    thresholdwidget->var_absThreshold_combobox->setCurrentIndex(sysf->load_sysparam((char*)"Pretreat", (char*)"Threshold", (char*)"VarAbsThreshold","").toInt());
    thresholdwidget->var_lightDark_combobox->setCurrentIndex(sysf->load_sysparam((char*)"Pretreat", (char*)"Threshold", (char*)"VarLightdark","").toInt());
    thresholdwidget->var_masksize_combobox->setCurrentIndex(sysf->load_sysparam((char*)"Pretreat", (char*)"Threshold", (char*)"VarMasksize","").toInt());
    thresholdwidget->var_stdDevScale_combobox->setCurrentIndex(sysf->load_sysparam((char*)"Pretreat", (char*)"Threshold", (char*)"VarStdDevScale","").toInt());
    //erosion
    erosion_presetwidget->checkbox->setChecked(sysf->load_sysparam((char*)"Pretreat",(char*)"Erosion",(char*)"IsChecked","").toInt());
    erosionwidget->se_size_combobox->setCurrentIndex(sysf->load_sysparam((char*)"Pretreat",(char*)"Erosion",(char*)"SeSize","").toInt());
    erosionwidget->se_type_combobox->setCurrentIndex(sysf->load_sysparam((char*)"Pretreat",(char*)"Erosion",(char*)"SeType","").toInt());
    //Dilation
    dilation_presetwidget->checkbox->setChecked(sysf->load_sysparam((char*)"Pretreat",(char*)"Dilation",(char*)"IsChecked","").toInt());
    dilationwidget->se_size_combobox->setCurrentIndex(sysf->load_sysparam((char*)"Pretreat",(char*)"Dilation",(char*)"SeSize","").toInt());
    dilationwidget->se_type_combobox->setCurrentIndex(sysf->load_sysparam((char*)"Pretreat",(char*)"Dilation",(char*)"SeType","").toInt());
    //Open
    opening_presetwidget->checkbox->setChecked(sysf->load_sysparam((char*)"Pretreat",(char*)"Opening",(char*)"IsChecked","").toInt());
    openingwidget->se_size_combobox->setCurrentIndex(sysf->load_sysparam((char*)"Pretreat",(char*)"Opening",(char*)"SeSize","").toInt());
    openingwidget->se_type_combobox->setCurrentIndex(sysf->load_sysparam((char*)"Pretreat",(char*)"Opening",(char*)"SeType","").toInt());
    //close
    closing_presetwidget->checkbox->setChecked(sysf->load_sysparam((char*)"Pretreat",(char*)"Closing",(char*)"IsChecked","").toInt());
    closingwidget->se_size_combobox->setCurrentIndex(sysf->load_sysparam((char*)"Pretreat",(char*)"Closing",(char*)"SeSize","").toInt());
    closingwidget->se_type_combobox->setCurrentIndex(sysf->load_sysparam((char*)"Pretreat",(char*)"Closing",(char*)"SeType","").toInt());
}

void PreTreatDialog::saveDefaultPara()
{
    sysfile *sysf=new sysfile(this);

    //scale
    sysf->save_sysparam((char*)"Pretreat",(char*)"Scale",(char*)"IsChecked",(QString::number(scaleimage_presetwidget->checkbox->isChecked())).toLatin1().data(),"");
    sysf->save_sysparam((char*)"Pretreat",(char*)"Scale",(char*)"Mult",scaleimagewidget->scaleimage_mult_lineedit->text().toLatin1().data(),"");
    sysf->save_sysparam((char*)"Pretreat",(char*)"Scale",(char*)"Add",scaleimagewidget->scaleimage_add_spinbox->text().toLatin1().data(),"");

    //illuminate
    sysf->save_sysparam((char*)"Pretreat",(char*)"Illuminate",(char*)"IsChecked",(QString::number(illuminate_presetwidget->checkbox->isChecked())).toLatin1().data(),"");
    sysf->save_sysparam((char*)"Pretreat",(char*)"Illuminate",(char*)"Factor",(QString::number(illuminatewidget->illuminate_factor_combobox->currentIndex())).toLatin1().data(),"");
    sysf->save_sysparam((char*)"Pretreat",(char*)"Illuminate",(char*)"MaskSize",(QString::number(illuminatewidget->illuminate_masksize_combobox->currentIndex())).toLatin1().data(),"");

    //mean
    sysf->save_sysparam((char*)"Pretreat",(char*)"Mean",(char*)"IsChecked",(QString::number(mean_presetwidget->checkbox->isChecked())).toLatin1().data(),"");
    sysf->save_sysparam((char*)"Pretreat",(char*)"Mean",(char*)"MaskSize",(QString::number(meanwidget->mean_masksize_combobox->currentIndex())).toLatin1().data(),"");

    //emphasize
    sysf->save_sysparam((char*)"Pretreat",(char*)"Emphasize",(char*)"IsChecked",(QString::number(emphasize_presetwidget->checkbox->isChecked())).toLatin1().data(),"");
    sysf->save_sysparam((char*)"Pretreat",(char*)"Emphasize",(char*)"Factor",(QString::number(emphasizewidget->emphasize_factor_combobox->currentIndex())).toLatin1().data(),"");
    sysf->save_sysparam((char*)"Pretreat",(char*)"Emphasize",(char*)"MaskSize",(QString::number(emphasizewidget->emphasize_masksize_combobox->currentIndex())).toLatin1().data(),"");

    //median
    sysf->save_sysparam((char*)"Pretreat",(char*)"Median",(char*)"IsChecked",(QString::number(median_presetwidget->checkbox->isChecked())).toLatin1().data(),"");
    sysf->save_sysparam((char*)"Pretreat",(char*)"Median",(char*)"Margin",(QString::number(medianwidget->median_margin_combobox->currentIndex())).toLatin1().data(),"");
    sysf->save_sysparam((char*)"Pretreat",(char*)"Median",(char*)"MaskType",(QString::number(medianwidget->median_masktype_combobox->currentIndex())).toLatin1().data(),"");
    sysf->save_sysparam((char*)"Pretreat",(char*)"Median",(char*)"Radius",(QString::number(medianwidget->median_radius_combobox->currentIndex())).toLatin1().data(),"");

    //decompose
    sysf->save_sysparam((char*)"Pretreat",(char*)"Decompose",(char*)"IsChecked",(QString::number(decompose_presetwidget->checkbox->isChecked())).toLatin1().data(),"");
    sysf->save_sysparam((char*)"Pretreat",(char*)"Decompose",(char*)"Choice",(QString::number(decomposewidget->decompose_combobox->currentIndex())).toLatin1().data(),"");

    //Threshold
    sysf->save_sysparam((char*)"Pretreat",(char*)"Threshold",(char*)"IsChecked",(QString::number(threshold_presetwidget->checkbox->isChecked())).toLatin1().data(),"");
    sysf->save_sysparam((char*)"Pretreat",(char*)"Threshold",(char*)"Choice",(QString::number(thresholdwidget->combobox->currentIndex())).toLatin1().data(),"");
    sysf->save_sysparam((char*)"Pretreat", (char*)"Threshold", (char*)"MinGray",thresholdwidget->mingray_spinBox->text().toLatin1().data(),"");
    sysf->save_sysparam((char*)"Pretreat", (char*)"Threshold", (char*)"MaxGray",thresholdwidget->maxgray_spinBox->text().toLatin1().data(),"");
    sysf->save_sysparam((char*)"Pretreat", (char*)"Threshold", (char*)"DualMinsize",thresholdwidget->dual_minsize_lineedit->text().toLatin1().data(),"");
    sysf->save_sysparam((char*)"Pretreat", (char*)"Threshold", (char*)"DualMingray",thresholdwidget->dual_mingray_spinBox->text().toLatin1().data(),"");
    sysf->save_sysparam((char*)"Pretreat", (char*)"Threshold", (char*)"DualThreshold",thresholdwidget->dual_threshold_spinBox->text().toLatin1().data(),"");
    sysf->save_sysparam((char*)"Pretreat", (char*)"Threshold", (char*)"VarAbsThreshold",(QString::number(thresholdwidget->var_absThreshold_combobox->currentIndex())).toLatin1().data(),"");
    sysf->save_sysparam((char*)"Pretreat", (char*)"Threshold", (char*)"VarLightdark",(QString::number(thresholdwidget->var_lightDark_combobox->currentIndex())).toLatin1().data(),"");
    sysf->save_sysparam((char*)"Pretreat", (char*)"Threshold", (char*)"VarMasksize",(QString::number(thresholdwidget->var_masksize_combobox->currentIndex())).toLatin1().data(),"");
    sysf->save_sysparam((char*)"Pretreat", (char*)"Threshold", (char*)"VarStdDevScale",(QString::number(thresholdwidget->var_stdDevScale_combobox->currentIndex())).toLatin1().data(),"");
    //erosion
    sysf->save_sysparam((char*)"Pretreat",(char*)"Erosion",(char*)"IsChecked",(QString::number(erosion_presetwidget->checkbox->isChecked())).toLatin1().data(),"");
    sysf->save_sysparam((char*)"Pretreat",(char*)"Erosion",(char*)"SeSize",(QString::number(erosionwidget->se_size_combobox->currentIndex())).toLatin1().data(),"");
    sysf->save_sysparam((char*)"Pretreat",(char*)"Erosion",(char*)"SeType",(QString::number(erosionwidget->se_type_combobox->currentIndex())).toLatin1().data(),"");
    //Dilation
    sysf->save_sysparam((char*)"Pretreat",(char*)"Dilation",(char*)"IsChecked",(QString::number(dilation_presetwidget->checkbox->isChecked())).toLatin1().data(),"");
    sysf->save_sysparam((char*)"Pretreat",(char*)"Dilation",(char*)"SeSize",(QString::number(dilationwidget->se_size_combobox->currentIndex())).toLatin1().data(),"");
    sysf->save_sysparam((char*)"Pretreat",(char*)"Dilation",(char*)"SeType",(QString::number(dilationwidget->se_type_combobox->currentIndex())).toLatin1().data(),"");
    //Open
    sysf->save_sysparam((char*)"Pretreat",(char*)"Opening",(char*)"IsChecked",(QString::number(opening_presetwidget->checkbox->isChecked())).toLatin1().data(),"");
    sysf->save_sysparam((char*)"Pretreat",(char*)"Opening",(char*)"SeSize",(QString::number(openingwidget->se_size_combobox->currentIndex())).toLatin1().data(),"");
    sysf->save_sysparam((char*)"Pretreat",(char*)"Opening",(char*)"SeType",(QString::number(openingwidget->se_type_combobox->currentIndex())).toLatin1().data(),"");
    //close
    sysf->save_sysparam((char*)"Pretreat",(char*)"Closing",(char*)"IsChecked",(QString::number(closing_presetwidget->checkbox->isChecked())).toLatin1().data(),"");
    sysf->save_sysparam((char*)"Pretreat",(char*)"Closing",(char*)"SeSize",(QString::number(closingwidget->se_size_combobox->currentIndex())).toLatin1().data(),"");
    sysf->save_sysparam((char*)"Pretreat",(char*)"Closing",(char*)"SeType",(QString::number(closingwidget->se_type_combobox->currentIndex())).toLatin1().data(),"");

}

void PreTreatDialog::pretreatImage(HObject *himage)
{
    HObject buffhimage=*himage;

    //按照顺序

    if(scaleimage_presetwidget->checkbox->isChecked())//亮度调节
    {
        double multvalue;
        int addvalue;
        HObject ho_ImageScaled;
              multvalue=scaleimagewidget->scaleimage_mult_lineedit->text().toDouble();
              addvalue=scaleimagewidget->scaleimage_add_spinbox->text().toInt();
              ScaleImage(buffhimage, &ho_ImageScaled, multvalue,addvalue);
              buffhimage=ho_ImageScaled;
    }

    if(illuminate_presetwidget->checkbox->isChecked())//亮度改善
    {
        int masksize;
        float factor;
        HObject ho_ImageIlluminate;
        masksize=illuminatewidget->illuminate_masksize_combobox->currentText().toInt();
        factor=illuminatewidget->illuminate_factor_combobox->currentText().toFloat();
        Illuminate(buffhimage, &ho_ImageIlluminate, masksize, masksize, factor);
        buffhimage=ho_ImageIlluminate;
    }

    if(mean_presetwidget->checkbox->isChecked())//模糊
    {
        int masksize;
        HObject ho_MeanImage;
        masksize=meanwidget->mean_masksize_combobox->currentText().toInt();
        MeanImage(buffhimage,&ho_MeanImage,masksize,masksize);
        buffhimage=ho_MeanImage;
    }

    if(emphasize_presetwidget->checkbox->isChecked())   //锐化
    {
        int masksize;
        float factor;
        HObject ho_ImageEmphasize;
        masksize=emphasizewidget->emphasize_masksize_combobox->currentText().toInt();
        factor=emphasizewidget->emphasize_factor_combobox->currentText().toFloat();
        Emphasize(buffhimage, &ho_ImageEmphasize, masksize, masksize, factor);
        buffhimage=ho_ImageEmphasize;
    }

    if(median_presetwidget->checkbox->isChecked())   //       中值滤波
    {
        HObject ho_ImageMedian;
        int Radius=medianwidget->median_radius_combobox->currentText().toInt();
        int masktypeIndex=medianwidget->median_masktype_combobox->currentIndex();
        int marginIndex=medianwidget->median_margin_combobox->currentIndex();
        int Margin;
        if(masktypeIndex==0)//circle
        {
            if(marginIndex==0)
            {
                MedianImage(buffhimage,&ho_ImageMedian,"circle" , Radius, "mirrored");
            }
            else if(marginIndex==1)
            {
                MedianImage(buffhimage,&ho_ImageMedian,"circle" , Radius, "cyclic");
            }
            else if(marginIndex==2)
            {
                MedianImage(buffhimage,&ho_ImageMedian,"circle" , Radius, "continued");
            }
            else
            {
                Margin=medianwidget->median_margin_combobox->currentText().toInt();
                MedianImage(buffhimage,&ho_ImageMedian,"circle" , Radius, Margin);
            }

        }
        else if(masktypeIndex==1)//square
        {
            if(marginIndex==0)
            {
                MedianImage(buffhimage,&ho_ImageMedian,"square" , Radius,"mirrored");
            }
            else if(marginIndex==1)
            {
                MedianImage(buffhimage,&ho_ImageMedian,"square" , Radius,"cyclic");

            }
            else if(marginIndex==2)
            {
                MedianImage(buffhimage,&ho_ImageMedian,"square" , Radius,"continued");
            }
            else
            {
                Margin=medianwidget->median_margin_combobox->currentText().toInt();
                MedianImage(buffhimage,&ho_ImageMedian,"square" , Radius, Margin);
            }

        }

        buffhimage=ho_ImageMedian;
    }

    if(decompose_presetwidget->checkbox->isChecked())//通道分解
    {
        HObject  ho_Red, ho_Green, ho_Blue;
        int choice;
        choice=decomposewidget->decompose_combobox->currentIndex();
        Decompose3(buffhimage,&ho_Red,&ho_Green,&ho_Blue);
        if(choice==0)
        {
            buffhimage=ho_Red;
        }
        else if(choice==1)
        {
            buffhimage=ho_Green;
        }
        else if(choice==2)
        {
            buffhimage=ho_Blue;
        }
    }

    if(threshold_presetwidget->checkbox->isChecked())//阈值划分
    {
        HObject ho_Region,ho_ConnectedRegions,ho_RegionImage;
        HTuple  hv_Width, hv_Height;
        if(thresholdwidget->combobox->currentIndex()==0)
        {
            mingray=thresholdwidget->mingray_spinBox->text().toInt();
            maxgray=thresholdwidget->maxgray_spinBox->text().toInt();

            if(mingray>maxgray)
            {
                QMessageBox::information(this,"information","mingray > maxgray !");
            }
            else
            {

                GetImageSize(buffhimage,&hv_Width,&hv_Height);

               Threshold(buffhimage, &ho_Region, mingray, maxgray);//阈值分割
              //    Threshold(ho_Image, &ho_Region, 0, 90);//阈值分割

                Connection(ho_Region, &ho_ConnectedRegions);
                RegionToBin(ho_ConnectedRegions,&ho_RegionImage,0,255,hv_Width,hv_Height);
                //将图像与区域转化成一个二进制字节图像。给区域内的所有像素赋予前景灰度值，区域外则赋予后景灰度值
                buffhimage = ho_RegionImage;
            }


        }
        if(thresholdwidget->combobox->currentIndex()==1)
        {
            dual_minsize=thresholdwidget->dual_minsize_lineedit->text().toInt();
            dual_mingray=thresholdwidget->dual_mingray_spinBox->text().toInt();
            dual_threshold=thresholdwidget->dual_threshold_spinBox->text().toInt();

            if(dual_mingray < dual_threshold)
            {
                QMessageBox::information(this,"information","in dual_threshold: the valve"
                                          " mingray has to be greater than valve threshold !");
            }
            else
            {

                GetImageSize(buffhimage,&hv_Width,&hv_Height);

                DualThreshold(buffhimage,&ho_Region,dual_minsize,dual_mingray,dual_threshold);

                Connection(ho_Region, &ho_ConnectedRegions);
                RegionToBin(ho_ConnectedRegions,&ho_RegionImage,0,255,hv_Width,hv_Height);
                //将图像与区域转化成一个二进制字节图像。给区域内的所有像素赋予前景灰度值，区域外则赋予后景灰度值
                buffhimage = ho_RegionImage;
            }


        }
        if(thresholdwidget->combobox->currentIndex()==2)
        {
            //获取数据
            int masksizecomboboxIndex;
            masksizecomboboxIndex=thresholdwidget->var_masksize_combobox->currentIndex();
            if(masksizecomboboxIndex==0)
            {
                var_masksize=9;
            }
            else if(masksizecomboboxIndex==1)
            {
                var_masksize=11;
            }
            else if(masksizecomboboxIndex==2)
            {
                var_masksize=13;
            }
            else if(masksizecomboboxIndex==3)
            {
                var_masksize=15;
            }

            var_stdDevScale=thresholdwidget->var_stdDevScale_combobox->currentText().toFloat();
            var_absThreshold=thresholdwidget->var_absThreshold_combobox->currentText().toInt();
            var_lightDark=thresholdwidget->var_lightDark_combobox->currentIndex();


            GetImageSize(buffhimage,&hv_Width,&hv_Height);

            if(var_lightDark==0)
            {
                VarThreshold(buffhimage,&ho_Region,var_masksize,var_masksize,var_stdDevScale
                             ,var_absThreshold,"dark");
            }
            else if(var_lightDark==1)
            {
                VarThreshold(buffhimage,&ho_Region,var_masksize,var_masksize,var_stdDevScale
                             ,var_absThreshold,"equal");
            }
            else if(var_lightDark==2)
            {
                VarThreshold(buffhimage,&ho_Region,var_masksize,var_masksize,var_stdDevScale
                             ,var_absThreshold,"light");
            }
            else if(var_lightDark==3)
            {
                VarThreshold(buffhimage,&ho_Region,var_masksize,var_masksize,var_stdDevScale
                             ,var_absThreshold,"not_equal");
            }


            Connection(ho_Region, &ho_ConnectedRegions);
            RegionToBin(ho_ConnectedRegions,&ho_RegionImage,0,255,hv_Width,hv_Height);
            //将图像与区域转化成一个二进制字节图像。给区域内的所有像素赋予前景灰度值，区域外则赋予后景灰度值
            buffhimage = ho_RegionImage;
        }

    }

    if(erosion_presetwidget->checkbox->isChecked())//腐蚀
    {
        int typeIndex=erosionwidget->se_type_combobox->currentIndex();
        int se_size=erosionwidget->se_size_combobox->currentText().toInt();
        HObject ho_ImageErosion;
        if(typeIndex==0)     //圆形
        {
            HObject ho_SE;
            GenDiscSe(&ho_SE, "byte",se_size, se_size, 0);
            GrayErosion(buffhimage, ho_SE, &ho_ImageErosion);
            buffhimage=ho_ImageErosion;
        }
        else if(typeIndex==1)//方形
        {
            GrayErosionRect(buffhimage,&ho_ImageErosion,se_size,se_size);
            buffhimage=ho_ImageErosion;
        }
    }

    if(dilation_presetwidget->checkbox->isChecked())//膨胀
    {
        int typeIndex=dilationwidget->se_type_combobox->currentIndex();
        int se_size=dilationwidget->se_size_combobox->currentText().toInt();
        HObject ho_ImageDilation;
        if(typeIndex==0)     //圆形
        {
            HObject ho_SE;
            GenDiscSe(&ho_SE, "byte",se_size, se_size, 0);
            GrayDilation(buffhimage, ho_SE, &ho_ImageDilation);
            buffhimage=ho_ImageDilation;
        }
        else if(typeIndex==1)//方形
        {
            GrayDilationRect(buffhimage,&ho_ImageDilation,se_size,se_size);
            buffhimage=ho_ImageDilation;
        }
    }

    if(opening_presetwidget->checkbox->isChecked())//开运算
    {
        int typeIndex=openingwidget->se_type_combobox->currentIndex();
        int se_size=openingwidget->se_size_combobox->currentText().toInt();
        HObject ho_ImageOpening;
        if(typeIndex==0)     //圆形
        {
            HObject ho_SE;
            GenDiscSe(&ho_SE, "byte",se_size, se_size, 0);
            GrayOpening(buffhimage, ho_SE, &ho_ImageOpening);
            buffhimage=ho_ImageOpening;
        }
        else if(typeIndex==1)//方形
        {
            GrayOpeningRect(buffhimage,&ho_ImageOpening,se_size,se_size);
            buffhimage=ho_ImageOpening;
        }
    }

    if(closing_presetwidget->checkbox->isChecked())//闭运算
    {
        int typeIndex=closingwidget->se_type_combobox->currentIndex();
        int se_size=closingwidget->se_size_combobox->currentText().toInt();
        HObject ho_ImageClosing;
        if(typeIndex==0)     //圆形
        {
            HObject ho_SE;
            GenDiscSe(&ho_SE, "byte",se_size, se_size, 0);
            GrayClosing(buffhimage, ho_SE, &ho_ImageClosing);
            buffhimage=ho_ImageClosing;
        }
        else if(typeIndex==1)//方形
        {
            GrayClosingRect(buffhimage,&ho_ImageClosing,se_size,se_size);
            buffhimage=ho_ImageClosing;
        }
    }

    *himage=buffhimage;
}

void PreTreatDialog::on_previewpushButton_clicked()
{
    previewImage=ho_Image;

    PreTreatDialog::pretreatImage(&previewImage);
    //按照顺序
/*
    if(scaleimage_presetwidget->checkbox->isChecked())//亮度调节
    {
        double multvalue;
        int addvalue;
        HObject ho_ImageScaled;
              multvalue=scaleimagewidget->scaleimage_mult_lineedit->text().toDouble();
              addvalue=scaleimagewidget->scaleimage_add_spinbox->text().toInt();
              ScaleImage(previewImage, &ho_ImageScaled, multvalue,addvalue);
              previewImage=ho_ImageScaled;
    }

    if(illuminate_presetwidget->checkbox->isChecked())//亮度改善
    {
        int masksize;
        float factor;
        HObject ho_ImageIlluminate;
        masksize=illuminatewidget->illuminate_masksize_combobox->currentText().toInt();
        factor=illuminatewidget->illuminate_factor_combobox->currentText().toFloat();
        Illuminate(previewImage, &ho_ImageIlluminate, masksize, masksize, factor);
        previewImage=ho_ImageIlluminate;
    }

    if(mean_presetwidget->checkbox->isChecked())//模糊
    {
        int masksize;
        HObject ho_MeanImage;
        masksize=meanwidget->mean_masksize_combobox->currentText().toInt();
        MeanImage(previewImage,&ho_MeanImage,masksize,masksize);
        previewImage=ho_MeanImage;
    }

    if(emphasize_presetwidget->checkbox->isChecked())   //锐化
    {
        int masksize;
        float factor;
        HObject ho_ImageEmphasize;
        masksize=emphasizewidget->emphasize_masksize_combobox->currentText().toInt();
        factor=emphasizewidget->emphasize_factor_combobox->currentText().toFloat();
        Emphasize(previewImage, &ho_ImageEmphasize, masksize, masksize, factor);
        previewImage=ho_ImageEmphasize;
    }

    if(median_presetwidget->checkbox->isChecked())   //       中值滤波
    {
        HObject ho_ImageMedian;
        int Radius=medianwidget->median_radius_combobox->currentText().toInt();
        int masktypeIndex=medianwidget->median_masktype_combobox->currentIndex();
        int marginIndex=medianwidget->median_margin_combobox->currentIndex();
        int Margin;
        if(masktypeIndex==0)//circle
        {
            if(marginIndex==0)
            {
                MedianImage(previewImage,&ho_ImageMedian,"circle" , Radius, "mirrored");
            }
            else if(marginIndex==1)
            {
                MedianImage(previewImage,&ho_ImageMedian,"circle" , Radius, "cyclic");
            }
            else if(marginIndex==2)
            {
                MedianImage(previewImage,&ho_ImageMedian,"circle" , Radius, "continued");
            }
            else
            {
                Margin=medianwidget->median_margin_combobox->currentText().toInt();
                MedianImage(previewImage,&ho_ImageMedian,"circle" , Radius, Margin);
            }

        }
        else if(masktypeIndex==1)//square
        {
            if(marginIndex==0)
            {
                MedianImage(previewImage,&ho_ImageMedian,"square" , Radius,"mirrored");
            }
            else if(marginIndex==1)
            {
                MedianImage(previewImage,&ho_ImageMedian,"square" , Radius,"cyclic");

            }
            else if(marginIndex==2)
            {
                MedianImage(previewImage,&ho_ImageMedian,"square" , Radius,"continued");
            }
            else
            {
                Margin=medianwidget->median_margin_combobox->currentText().toInt();
                MedianImage(previewImage,&ho_ImageMedian,"square" , Radius, Margin);
            }

        }

        previewImage=ho_ImageMedian;
    }

    if(decompose_presetwidget->checkbox->isChecked())//通道分解
    {
        HObject  ho_Red, ho_Green, ho_Blue;
        int choice;
        choice=decomposewidget->decompose_combobox->currentIndex();
        Decompose3(previewImage,&ho_Red,&ho_Green,&ho_Blue);
        if(choice==0)
        {
            previewImage=ho_Red;
        }
        else if(choice==1)
        {
            previewImage=ho_Green;
        }
        else if(choice==2)
        {
            previewImage=ho_Blue;
        }
    }

    if(threshold_presetwidget->checkbox->isChecked())//阈值划分
    {
        HObject ho_Region,ho_ConnectedRegions,ho_RegionImage;
        HTuple  hv_Width, hv_Height;
        if(thresholdwidget->combobox->currentIndex()==0)
        {
            mingray=thresholdwidget->mingray_spinBox->text().toInt();
            maxgray=thresholdwidget->maxgray_spinBox->text().toInt();

            if(mingray>maxgray)
            {
                QMessageBox::information(this,"information","mingray > maxgray !");
            }
            else
            {

                GetImageSize(previewImage,&hv_Width,&hv_Height);

               Threshold(previewImage, &ho_Region, mingray, maxgray);//阈值分割
              //    Threshold(ho_Image, &ho_Region, 0, 90);//阈值分割

                Connection(ho_Region, &ho_ConnectedRegions);
                RegionToBin(ho_ConnectedRegions,&ho_RegionImage,0,255,hv_Width,hv_Height);
                //将图像与区域转化成一个二进制字节图像。给区域内的所有像素赋予前景灰度值，区域外则赋予后景灰度值
                previewImage = ho_RegionImage;
            }


        }
        if(thresholdwidget->combobox->currentIndex()==1)
        {
            dual_minsize=thresholdwidget->dual_minsize_lineedit->text().toInt();
            dual_mingray=thresholdwidget->dual_mingray_spinBox->text().toInt();
            dual_threshold=thresholdwidget->dual_threshold_spinBox->text().toInt();

            if(dual_mingray < dual_threshold)
            {
                QMessageBox::information(this,"information","in dual_threshold: the valve"
                                          " mingray has to be greater than valve threshold !");
            }
            else
            {

                GetImageSize(previewImage,&hv_Width,&hv_Height);

                DualThreshold(previewImage,&ho_Region,dual_minsize,dual_mingray,dual_threshold);

                Connection(ho_Region, &ho_ConnectedRegions);
                RegionToBin(ho_ConnectedRegions,&ho_RegionImage,0,255,hv_Width,hv_Height);
                //将图像与区域转化成一个二进制字节图像。给区域内的所有像素赋予前景灰度值，区域外则赋予后景灰度值
                previewImage = ho_RegionImage;
            }


        }
        if(thresholdwidget->combobox->currentIndex()==2)
        {
            //获取数据
            int masksizecomboboxIndex;
            masksizecomboboxIndex=thresholdwidget->var_masksize_combobox->currentIndex();
            if(masksizecomboboxIndex==0)
            {
                var_masksize=9;
            }
            else if(masksizecomboboxIndex==1)
            {
                var_masksize=11;
            }
            else if(masksizecomboboxIndex==2)
            {
                var_masksize=13;
            }
            else if(masksizecomboboxIndex==3)
            {
                var_masksize=15;
            }

            var_stdDevScale=thresholdwidget->var_stdDevScale_combobox->currentText().toFloat();
            var_absThreshold=thresholdwidget->var_absThreshold_combobox->currentText().toInt();
            var_lightDark=thresholdwidget->var_lightDark_combobox->currentIndex();


            GetImageSize(previewImage,&hv_Width,&hv_Height);

            if(var_lightDark==0)
            {
                VarThreshold(previewImage,&ho_Region,var_masksize,var_masksize,var_stdDevScale
                             ,var_absThreshold,"dark");
            }
            else if(var_lightDark==1)
            {
                VarThreshold(previewImage,&ho_Region,var_masksize,var_masksize,var_stdDevScale
                             ,var_absThreshold,"equal");
            }
            else if(var_lightDark==2)
            {
                VarThreshold(previewImage,&ho_Region,var_masksize,var_masksize,var_stdDevScale
                             ,var_absThreshold,"light");
            }
            else if(var_lightDark==3)
            {
                VarThreshold(previewImage,&ho_Region,var_masksize,var_masksize,var_stdDevScale
                             ,var_absThreshold,"not_equal");
            }


            Connection(ho_Region, &ho_ConnectedRegions);
            RegionToBin(ho_ConnectedRegions,&ho_RegionImage,0,255,hv_Width,hv_Height);
            //将图像与区域转化成一个二进制字节图像。给区域内的所有像素赋予前景灰度值，区域外则赋予后景灰度值
            previewImage = ho_RegionImage;
        }

    }

    if(erosion_presetwidget->checkbox->isChecked())//腐蚀
    {
        int typeIndex=erosionwidget->se_type_combobox->currentIndex();
        int se_size=erosionwidget->se_size_combobox->currentText().toInt();
        HObject ho_ImageErosion;
        if(typeIndex==0)     //圆形
        {
            HObject ho_SE;
            GenDiscSe(&ho_SE, "byte",se_size, se_size, 0);
            GrayErosion(previewImage, ho_SE, &ho_ImageErosion);
            previewImage=ho_ImageErosion;
        }
        else if(typeIndex==1)//方形
        {
            GrayErosionRect(previewImage,&ho_ImageErosion,se_size,se_size);
            previewImage=ho_ImageErosion;
        }
    }

    if(dilation_presetwidget->checkbox->isChecked())//膨胀
    {
        int typeIndex=dilationwidget->se_type_combobox->currentIndex();
        int se_size=dilationwidget->se_size_combobox->currentText().toInt();
        HObject ho_ImageDilation;
        if(typeIndex==0)     //圆形
        {
            HObject ho_SE;
            GenDiscSe(&ho_SE, "byte",se_size, se_size, 0);
            GrayDilation(previewImage, ho_SE, &ho_ImageDilation);
            previewImage=ho_ImageDilation;
        }
        else if(typeIndex==1)//方形
        {
            GrayDilationRect(previewImage,&ho_ImageDilation,se_size,se_size);
            previewImage=ho_ImageDilation;
        }
    }

    if(opening_presetwidget->checkbox->isChecked())//开运算
    {
        int typeIndex=openingwidget->se_type_combobox->currentIndex();
        int se_size=openingwidget->se_size_combobox->currentText().toInt();
        HObject ho_ImageOpening;
        if(typeIndex==0)     //圆形
        {
            HObject ho_SE;
            GenDiscSe(&ho_SE, "byte",se_size, se_size, 0);
            GrayOpening(previewImage, ho_SE, &ho_ImageOpening);
            previewImage=ho_ImageOpening;
        }
        else if(typeIndex==1)//方形
        {
            GrayOpeningRect(previewImage,&ho_ImageOpening,se_size,se_size);
            previewImage=ho_ImageOpening;
        }
    }

    if(closing_presetwidget->checkbox->isChecked())//闭运算
    {
        int typeIndex=closingwidget->se_type_combobox->currentIndex();
        int se_size=closingwidget->se_size_combobox->currentText().toInt();
        HObject ho_ImageClosing;
        if(typeIndex==0)     //圆形
        {
            HObject ho_SE;
            GenDiscSe(&ho_SE, "byte",se_size, se_size, 0);
            GrayClosing(previewImage, ho_SE, &ho_ImageClosing);
            previewImage=ho_ImageClosing;
        }
        else if(typeIndex==1)//方形
        {
            GrayClosingRect(previewImage,&ho_ImageClosing,se_size,se_size);
            previewImage=ho_ImageClosing;
        }
    }
*/
    QImage *image=new QImage;
    showimage.HtoQimage(previewImage,&image);
    showPicture(image);
}
