#include "erosionanddilation_widget.h"

erosionanddilation_widget::erosionanddilation_widget(QWidget *parent) : QWidget(parent)
{
    QGridLayout *glayout=new QGridLayout;

    QLabel *se_type_label=new QLabel("结构元素类型");
    QLabel *se_size_label=new QLabel("结构元素size");

    se_type_combobox=new QComboBox;
    se_size_combobox=new QComboBox;

    se_type_combobox->addItem("圆形");
    se_type_combobox->addItem("方形");

    se_size_combobox->addItem("3");
    se_size_combobox->addItem("5");
    se_size_combobox->addItem("7");
    se_size_combobox->addItem("9");
    se_size_combobox->addItem("11");
    se_size_combobox->addItem("13");
    se_size_combobox->addItem("15");
    se_size_combobox->setEditable(true);

    glayout->addWidget(se_type_label,0,0);
    glayout->addWidget(se_type_combobox,0,1);

    glayout->addWidget(se_size_label,1,0);
    glayout->addWidget(se_size_combobox,1,1);

    this->setLayout(glayout);
}
