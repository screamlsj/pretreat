#ifndef SCALEINPUTDIALOG_H
#define SCALEINPUTDIALOG_H

#include <QDialog>

namespace Ui {
class ScaleInputDialog;
}

class ScaleInputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ScaleInputDialog(QWidget *parent = 0);
    ~ScaleInputDialog();

    double getMultValue();
    int getAddValue();

private:
    Ui::ScaleInputDialog *ui;
};

#endif // SCALEINPUTDIALOG_H
