#ifndef EMPHASIZEDIALOG_H
#define EMPHASIZEDIALOG_H

#include <QDialog>

namespace Ui {
class EmphasizeDialog;
}

class EmphasizeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EmphasizeDialog(QWidget *parent = 0);
    ~EmphasizeDialog();
    void getEmphasizeIndex(int *,float *);


private:
    Ui::EmphasizeDialog *ui;
};

#endif // EMPHASIZEDIALOG_H
