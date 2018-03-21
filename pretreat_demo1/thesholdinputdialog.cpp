#include "thesholdinputdialog.h"
#include "ui_thesholdinputdialog.h"

ThesholdInputDialog::ThesholdInputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ThesholdInputDialog)
{
    ui->setupUi(this);
}

ThesholdInputDialog::~ThesholdInputDialog()
{
    delete ui;
}
