#ifndef SCALEMAXDIALOG_H
#define SCALEMAXDIALOG_H

#include <QDialog>

namespace Ui {
class ScaleMaxDialog;
}

class ScaleMaxDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ScaleMaxDialog(QWidget *parent = 0);
    ~ScaleMaxDialog();
    int getScaleMaxChoice();

private:
    Ui::ScaleMaxDialog *ui;
};

#endif // SCALEMAXDIALOG_H
