#include "threshold_widget.h"

threshold_widget::threshold_widget(QWidget *parent) : QWidget(parent)
{
    vlayout=new QVBoxLayout;

    combobox=new QComboBox;
    combobox->addItem("threshold");
    combobox->addItem("dual_threshold");
    combobox->addItem("var_threshold");

    vlayout->addWidget(combobox);

    stackedwidget=new QStackedWidget;

    thresholdpage=new QWidget;
    dualthresholdpage=new QWidget;
    varthresholdpage=new QWidget;
    QLabel *label1=new QLabel("threshold settings");
    QLabel *label2=new QLabel("dual_threshold settings");
    QLabel *label3=new QLabel("var_threshold settings");

    QGridLayout *page1_vlayout=new QGridLayout;
    QGridLayout *page2_vlayout=new QGridLayout;
    QGridLayout *page3_vlayout=new QGridLayout;

    page1_vlayout->addWidget(label1,0,0,1,2);
    page2_vlayout->addWidget(label2,0,0,1,2);
    page3_vlayout->addWidget(label3,0,0,1,2);

    //threshold setting items
    QLabel *mingray_label=new QLabel("min grayValve");
    QLabel *maxgray_label=new QLabel("max grayValve");

    mingray_spinBox = new QSpinBox;
    QSlider *mingray_slider = new QSlider(Qt::Horizontal);
    mingray_spinBox->setRange(0,255);
    mingray_slider->setRange(0,255);
    QObject::connect(mingray_spinBox,SIGNAL(valueChanged(int)),mingray_slider,SLOT(setValue(int))); //将spinBox的数值传向slider信号槽
    QObject::connect(mingray_slider,SIGNAL(valueChanged(int)),mingray_spinBox,SLOT(setValue(int)));//将slider的数值传向spinBox信号槽
    mingray_spinBox->setValue(0);
    page1_vlayout->addWidget(mingray_label,1,0);
    page1_vlayout->addWidget(mingray_spinBox,1,1);
    page1_vlayout->addWidget(mingray_slider,1,2);

    maxgray_spinBox = new QSpinBox;
    QSlider *maxgray_slider = new QSlider(Qt::Horizontal);
    maxgray_spinBox->setRange(0,255);
    maxgray_slider->setRange(0,255);
    QObject::connect(maxgray_spinBox,SIGNAL(valueChanged(int)),maxgray_slider,SLOT(setValue(int))); //将spinBox的数值传向slider信号槽
    QObject::connect(maxgray_slider,SIGNAL(valueChanged(int)),maxgray_spinBox,SLOT(setValue(int)));//将slider的数值传向spinBox信号槽
    maxgray_spinBox->setValue(90);
    page1_vlayout->addWidget(maxgray_label,2,0);
    page1_vlayout->addWidget(maxgray_spinBox,2,1);
    page1_vlayout->addWidget(maxgray_slider,2,2);

    //dual_threshold setting items
    QLabel *dual_minsize_label=new QLabel("minSize");
    QLabel *dual_mingray_label=new QLabel("minGray");
    QLabel *dual_threshold_label=new QLabel("threshold");
    QLabel *dual_explain1=new QLabel("(MinSize表示分割出来的区域\n的最小面积（即数像素的数目个数）)");
    QLabel *dual_explain2=new QLabel("(MinGray表示分割出来的区域\n对应的原图中图像像素的最高灰度\n不能低于MinGray设定值)");
    QLabel *dual_explain3=new QLabel("(Threshold 表示用于分割的\n阈值数值)");
    dual_minsize_lineedit=new QLineEdit;
    dual_mingray_spinBox=new QSpinBox;
    dual_threshold_spinBox=new QSpinBox;
    QSlider *dual_mingray_slider=new QSlider(Qt::Horizontal);
    QSlider *dual_threshold_slider=new QSlider(Qt::Horizontal);
    dual_mingray_spinBox->setRange(0,255);//设置取值范围
    dual_mingray_slider->setRange(0,255);
    dual_threshold_spinBox->setRange(0,255);
    dual_threshold_slider->setRange(0,255);
    dual_mingray_spinBox->setValue(90);//设置初始值
    dual_mingray_slider->setValue(90);
    dual_threshold_spinBox->setValue(90);
    dual_threshold_slider->setValue(90);
    dual_minsize_lineedit->setText("0");

    QObject::connect(dual_mingray_slider,SIGNAL(valueChanged(int)),dual_mingray_spinBox,SLOT(setValue(int)));
    QObject::connect(dual_mingray_spinBox,SIGNAL(valueChanged(int)),dual_mingray_slider,SLOT(setValue(int)));
    QObject::connect(dual_threshold_spinBox,SIGNAL(valueChanged(int)),dual_threshold_slider,SLOT(setValue(int)));
    QObject::connect(dual_threshold_slider,SIGNAL(valueChanged(int)),dual_threshold_spinBox,SLOT(setValue(int)));

    dual_minsize_lineedit->setMaximumWidth(50);

    page2_vlayout->addWidget(dual_minsize_label,1,0);
    page2_vlayout->addWidget(dual_mingray_label,4,0);
    page2_vlayout->addWidget(dual_threshold_label,8,0);

    page2_vlayout->addWidget(dual_minsize_lineedit,1,1);
    page2_vlayout->addWidget(dual_mingray_spinBox,4,1);
    page2_vlayout->addWidget(dual_threshold_spinBox,8,1);

    page2_vlayout->addWidget(dual_mingray_slider,4,2);
    page2_vlayout->addWidget(dual_threshold_slider,8,2);

    page2_vlayout->addWidget(dual_explain1,2,0,2,3);
    page2_vlayout->addWidget(dual_explain2,5,0,3,3);
    page2_vlayout->addWidget(dual_explain3,9,0,2,3);

    //var_threshold setting items

    QLabel *var_masksize_label=new QLabel("maskSize");
    QLabel *var_stdDevScale_label=new QLabel("stdDevScale");
    QLabel *var_absThreshold_label=new QLabel("AbsThreshold");
    QLabel *var_lightDark_label=new QLabel("lightDark");

    var_masksize_combobox=new QComboBox;
    var_stdDevScale_combobox=new QComboBox;
    var_absThreshold_combobox=new QComboBox;
    var_lightDark_combobox=new QComboBox;

    var_masksize_combobox->addItem("'9*9'");
    var_masksize_combobox->addItem("'11*11'");
    var_masksize_combobox->addItem("'13*13'");
    var_masksize_combobox->addItem("'15*15'");

    var_stdDevScale_combobox->addItem("-0.2");
    var_stdDevScale_combobox->addItem("-0.1");
    var_stdDevScale_combobox->addItem("0.1");
    var_stdDevScale_combobox->addItem("0.2");

    var_absThreshold_combobox->addItem("-2");
    var_absThreshold_combobox->addItem("-1");
    var_absThreshold_combobox->addItem("0");
    var_absThreshold_combobox->addItem("1");
    var_absThreshold_combobox->addItem("2");

    //var_absThreshold_combobox->setEditable(true);

    var_lightDark_combobox->addItem("dark");
    var_lightDark_combobox->addItem("equal");
    var_lightDark_combobox->addItem("light");
    var_lightDark_combobox->addItem("not_equal");

    page3_vlayout->addWidget(var_masksize_label,1,0);
    page3_vlayout->addWidget(var_stdDevScale_label,2,0);
    page3_vlayout->addWidget(var_absThreshold_label,3,0);
    page3_vlayout->addWidget(var_lightDark_label,4,0);

    page3_vlayout->addWidget(var_masksize_combobox,1,1);
    page3_vlayout->addWidget(var_stdDevScale_combobox,2,1);
    page3_vlayout->addWidget(var_absThreshold_combobox,3,1);
    page3_vlayout->addWidget(var_lightDark_combobox,4,1);


    //---------------------------------------------


    thresholdpage->setLayout(page1_vlayout);
    dualthresholdpage->setLayout(page2_vlayout);
    varthresholdpage->setLayout(page3_vlayout);

    stackedwidget->addWidget(thresholdpage);
    stackedwidget->addWidget(dualthresholdpage);
    stackedwidget->addWidget(varthresholdpage);

    vlayout->addWidget(stackedwidget);

    setLayout(vlayout);
    connect(this->combobox,SIGNAL(currentIndexChanged(int)),this,SLOT(switchpage(int)));
}

void threshold_widget::switchpage(int index)
{
    index=combobox->currentIndex();
    stackedwidget->setCurrentIndex(index);
}
