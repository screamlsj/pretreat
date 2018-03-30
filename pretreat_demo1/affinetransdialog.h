#ifndef AFFINETRANSDIALOG_H
#define AFFINETRANSDIALOG_H

#include <QDialog>

namespace Ui {
class AffineTransDialog;
}

class AffineTransDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AffineTransDialog(QWidget *parent = 0);
    ~AffineTransDialog();
    void getAffineIndex(float *,int *,int *,float *,float *,int *,int *);


private:
    Ui::AffineTransDialog *ui;
};

#endif // AFFINETRANSDIALOG_H
