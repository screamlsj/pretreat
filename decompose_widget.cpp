#include "decompose_widget.h"

decompose_widget::decompose_widget(QWidget *parent) : QWidget(parent)
{
    QGridLayout *glayout=new QGridLayout;

    QLabel *decompose_label=new QLabel("选择分解得到的频道");

    decompose_combobox=new QComboBox;
    decompose_combobox->addItem("r");
    decompose_combobox->addItem("g");
    decompose_combobox->addItem("b");

    glayout->addWidget(decompose_label,0,0);
    glayout->addWidget(decompose_combobox,1,0);

    this->setLayout(glayout);

}
