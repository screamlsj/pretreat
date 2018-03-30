#include "geometrictransdialog.h"
#include "ui_geometrictransdialog.h"

GeometricTransDialog::GeometricTransDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GeometricTransDialog)
{
    ui->setupUi(this);
}

GeometricTransDialog::~GeometricTransDialog()
{
    delete ui;
}
