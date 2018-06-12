#include "scaleimage_widget.h"

scaleimage_widget::scaleimage_widget(QWidget *parent) : QWidget(parent)
{
    QGridLayout *glayout=new QGridLayout;

    QLabel *scaleimage_fun_label=new QLabel("g' := g * Mult + Add");
    QLabel *scaleimage_mult_label=new QLabel("mult");
    QLabel *scaleimage_add_label=new QLabel("add");
    QLabel *scaleimage_mult_incre_label=new QLabel("精度 0.001");

    scaleimage_mult_lineedit=new QLineEdit;
    scaleimage_add_spinbox=new QSpinBox;

    QSlider *scaleimage_add_slider=new QSlider;

    scaleimage_mult_lineedit->setText("1");
    scaleimage_add_spinbox->setRange(0,255);
    scaleimage_add_slider->setRange(0,255);
    scaleimage_add_spinbox->setValue(20);
    scaleimage_add_slider->setValue(20);

    QObject::connect(scaleimage_add_spinbox,SIGNAL(valueChanged(int)),scaleimage_add_slider,SLOT(setValue(int))); //将spinBox的数值传向slider信号槽
    QObject::connect(scaleimage_add_slider,SIGNAL(valueChanged(int)),scaleimage_add_spinbox,SLOT(setValue(int)));//将slider的数值传向spinBox信号槽

    glayout->addWidget(scaleimage_fun_label,0,0,1,3);
    glayout->addWidget(scaleimage_mult_label,1,0);
    glayout->addWidget(scaleimage_mult_lineedit,1,1);
    glayout->addWidget(scaleimage_mult_incre_label,1,2);

    glayout->addWidget(scaleimage_add_label,2,0);
    glayout->addWidget(scaleimage_add_spinbox,2,1);
    glayout->addWidget(scaleimage_add_slider,2,2);

    this->setLayout(glayout);

}
