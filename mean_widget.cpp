#include "mean_widget.h"

mean_widget::mean_widget(QWidget *parent) : QWidget(parent)
{
    QGridLayout *glayout=new QGridLayout;

    QLabel *mean_masksize_label=new QLabel("maskSize");

    mean_masksize_combobox=new QComboBox;

    mean_masksize_combobox->addItem("3");
    mean_masksize_combobox->addItem("5");
    mean_masksize_combobox->addItem("7");
    mean_masksize_combobox->addItem("9");
    mean_masksize_combobox->addItem("11");
    mean_masksize_combobox->addItem("15");
    mean_masksize_combobox->addItem("23");
    mean_masksize_combobox->addItem("31");
    mean_masksize_combobox->addItem("43");
    mean_masksize_combobox->addItem("61");
    mean_masksize_combobox->addItem("101");
    mean_masksize_combobox->setEditable(true);

    glayout->addWidget(mean_masksize_label,0,0);
    glayout->addWidget(mean_masksize_combobox,0,1);

    this->setLayout(glayout);
}
