#include "emphasizedialog.h"
#include "ui_emphasizedialog.h"

EmphasizeDialog::EmphasizeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EmphasizeDialog)
{
    ui->setupUi(this);
}

EmphasizeDialog::~EmphasizeDialog()
{
    delete ui;
}
