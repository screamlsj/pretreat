#include "decomposedialog.h"
#include "ui_decomposedialog.h"

DecomposeDialog::DecomposeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DecomposeDialog)
{
    ui->setupUi(this);
}

DecomposeDialog::~DecomposeDialog()
{
    delete ui;
}
