#include "illuminate_widget.h"

illuminate_widget::illuminate_widget(QWidget *parent) : QWidget(parent)
{
    QGridLayout *glayout=new QGridLayout;

    QLabel *illuminate_label=new QLabel("公式\nnew=round((val-mean)*Factor+orig).\n设置参数");
    QLabel *illuminate_masksize_label=new QLabel("maskSize");
    QLabel *illuminate_factor_label=new QLabel("factor");
    QLabel *illuminate_masksize_range_label=new QLabel(" 3 ≤ MaskSize ≤ 299");
    QLabel *illuminate_factor_range_label=new QLabel("0.0 ≤ Factor ≤ 5.0");

    illuminate_masksize_combobox=new QComboBox;
    illuminate_factor_combobox=new QComboBox;

    illuminate_masksize_combobox->addItem("31");
    illuminate_masksize_combobox->addItem("41");
    illuminate_masksize_combobox->addItem("51");
    illuminate_masksize_combobox->addItem("71");
    illuminate_masksize_combobox->addItem("101");
    illuminate_masksize_combobox->addItem("121");
    illuminate_masksize_combobox->addItem("151");
    illuminate_masksize_combobox->addItem("201");
    illuminate_masksize_combobox->setEditable(true);

    illuminate_factor_combobox->addItem("0.3");
    illuminate_factor_combobox->addItem("0.5");
    illuminate_factor_combobox->addItem("0.7");
    illuminate_factor_combobox->addItem("1.0");
    illuminate_factor_combobox->addItem("1.5");
    illuminate_factor_combobox->addItem("2.0");
    illuminate_factor_combobox->addItem("3.0");
    illuminate_factor_combobox->addItem("5.0");
    illuminate_factor_combobox->setEditable(true);

    glayout->addWidget(illuminate_label,0,0,1,3);
    glayout->addWidget(illuminate_masksize_label,1,0);
    glayout->addWidget(illuminate_masksize_combobox,1,1);
    glayout->addWidget(illuminate_masksize_range_label,1,2);
    glayout->addWidget(illuminate_factor_label,2,0);
    glayout->addWidget(illuminate_factor_combobox,2,1);
    glayout->addWidget(illuminate_factor_range_label,2,2);

    this->setLayout(glayout);

}
