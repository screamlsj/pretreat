#include "comparedialog.h"
#include "ui_comparedialog.h"

CompareDialog::CompareDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CompareDialog)
{
    ui->setupUi(this);
}

CompareDialog::~CompareDialog()
{
    delete ui;
}

QString fileName2;

void CompareDialog::on_pushButton_clicked()
{
    fileName2 = QFileDialog::getOpenFileName(this,tr("open image file"), "", tr("Image files(*.jpg *.png);;All files (*.*)"));
    ui->label->setText(fileName2);
}
