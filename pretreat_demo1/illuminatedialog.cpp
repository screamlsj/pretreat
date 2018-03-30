#include "illuminatedialog.h"
#include "ui_illuminatedialog.h"

IlluminateDialog::IlluminateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IlluminateDialog)
{
    ui->setupUi(this);
}

IlluminateDialog::~IlluminateDialog()
{
    delete ui;
}
