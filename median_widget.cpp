#include "median_widget.h"

median_widget::median_widget(QWidget *parent) : QWidget(parent)
{
    QGridLayout *glayout=new QGridLayout;

    QLabel *median_masktype_label=new QLabel("掩膜类型");
    QLabel *median_radius_label=new QLabel("掩膜半径");
    QLabel *median_margin_label=new QLabel("图像外假设值");

    median_masktype_combobox=new QComboBox;
    median_radius_combobox=new QComboBox;
    median_margin_combobox=new QComboBox;

    median_masktype_combobox->addItem("圆形");
    median_masktype_combobox->addItem("方形");

    median_radius_combobox->addItem("1");
    median_radius_combobox->addItem("2");
    median_radius_combobox->addItem("3");
    median_radius_combobox->addItem("4");
    median_radius_combobox->addItem("5");
    median_radius_combobox->addItem("6");
    median_radius_combobox->addItem("7");
    median_radius_combobox->addItem("8");
    median_radius_combobox->addItem("9");
    median_radius_combobox->addItem("11");
    median_radius_combobox->addItem("15");
    median_radius_combobox->addItem("19");
    median_radius_combobox->addItem("25");
    median_radius_combobox->addItem("31");
    median_radius_combobox->addItem("39");
    median_radius_combobox->addItem("47");
    median_radius_combobox->addItem("59");
    median_radius_combobox->setEditable(true);

    median_margin_combobox->addItem("mirrored");
    median_margin_combobox->addItem("cyclic");
    median_margin_combobox->addItem("continued");
    median_margin_combobox->addItem("0");
    median_margin_combobox->addItem("30");
    median_margin_combobox->addItem("60");
    median_margin_combobox->addItem("90");
    median_margin_combobox->addItem("120");
    median_margin_combobox->addItem("150");
    median_margin_combobox->addItem("180");
    median_margin_combobox->addItem("210");
    median_margin_combobox->addItem("240");
    median_margin_combobox->addItem("255");
    median_margin_combobox->setEditable(true);

    glayout->addWidget(median_masktype_label,0,0);
    glayout->addWidget(median_masktype_combobox,0,1);
    glayout->addWidget(median_radius_label,1,0);
    glayout->addWidget(median_radius_combobox,1,1);
    glayout->addWidget(median_margin_label,2,0);
    glayout->addWidget(median_margin_combobox,2,1);

    this->setLayout(glayout);

}
