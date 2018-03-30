#ifndef ILLUMINATEDIALOG_H
#define ILLUMINATEDIALOG_H

#include <QDialog>

namespace Ui {
class IlluminateDialog;
}

class IlluminateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit IlluminateDialog(QWidget *parent = 0);
    ~IlluminateDialog();
    void getIlluminateIndex(int *,float *);

private:
    Ui::IlluminateDialog *ui;
};

#endif // ILLUMINATEDIALOG_H
