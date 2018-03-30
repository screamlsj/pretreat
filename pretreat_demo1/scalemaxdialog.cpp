#include "scalemaxdialog.h"
#include "ui_scalemaxdialog.h"

ScaleMaxDialog::ScaleMaxDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScaleMaxDialog)
{
    ui->setupUi(this);
}

ScaleMaxDialog::~ScaleMaxDialog()
{
    delete ui;
}
