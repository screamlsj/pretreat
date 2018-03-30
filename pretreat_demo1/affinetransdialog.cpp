#include "affinetransdialog.h"
#include "ui_affinetransdialog.h"

AffineTransDialog::AffineTransDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AffineTransDialog)
{
    ui->setupUi(this);
}

AffineTransDialog::~AffineTransDialog()
{
    delete ui;
}
