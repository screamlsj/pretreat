#include "scaleinputdialog.h"
#include "ui_scaleinputdialog.h"

ScaleInputDialog::ScaleInputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScaleInputDialog)
{
    ui->setupUi(this);
}

ScaleInputDialog::~ScaleInputDialog()
{
    delete ui;
}
