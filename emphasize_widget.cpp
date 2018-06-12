#include "emphasize_widget.h"

emphasize_widget::emphasize_widget(QWidget *parent) : QWidget(parent)
{
    QGridLayout *glayout=new QGridLayout;

    QLabel *emphasize_label=new QLabel("公式\nres=round((val-mean)*Factor+orig).\n设置参数");
    QLabel *emphasize_masksize_label=new QLabel("maskSize");
    QLabel *emphasize_factor_label=new QLabel("factor");
    QLabel *emphasize_masksize_range_label=new QLabel(" 3 ≤ MaskSize ≤ 201");
    QLabel *emphasize_factor_range_label=new QLabel("0.0 ≤ Factor ≤ 20.0(sqrt)");

    emphasize_masksize_combobox=new QComboBox;
    emphasize_factor_combobox=new QComboBox;

    emphasize_masksize_combobox->addItem("3");
    emphasize_masksize_combobox->addItem("5");
    emphasize_masksize_combobox->addItem("7");
    emphasize_masksize_combobox->addItem("9");
    emphasize_masksize_combobox->addItem("11");
    emphasize_masksize_combobox->addItem("15");
    emphasize_masksize_combobox->addItem("21");
    emphasize_masksize_combobox->addItem("25");
    emphasize_masksize_combobox->addItem("31");
    emphasize_masksize_combobox->addItem("39");
    emphasize_masksize_combobox->setEditable(true);

    emphasize_factor_combobox->addItem("0.3");
    emphasize_factor_combobox->addItem("0.5");
    emphasize_factor_combobox->addItem("0.7");
    emphasize_factor_combobox->addItem("1.0");
    emphasize_factor_combobox->addItem("1.4");
    emphasize_factor_combobox->addItem("1.8");
    emphasize_factor_combobox->addItem("2.0");
    emphasize_factor_combobox->setEditable(true);

    glayout->addWidget(emphasize_label,0,0,1,3);
    glayout->addWidget(emphasize_masksize_label,1,0);
    glayout->addWidget(emphasize_masksize_combobox,1,1);
    glayout->addWidget(emphasize_masksize_range_label,1,2);
    glayout->addWidget(emphasize_factor_label,2,0);
    glayout->addWidget(emphasize_factor_combobox,2,1);
    glayout->addWidget(emphasize_factor_range_label,2,2);

    this->setLayout(glayout);
}
