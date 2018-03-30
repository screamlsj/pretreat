#ifndef DECOMPOSEDIALOG_H
#define DECOMPOSEDIALOG_H

#include <QDialog>

namespace Ui {
class DecomposeDialog;
}

class DecomposeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DecomposeDialog(QWidget *parent = 0);
    ~DecomposeDialog();
    int getChoice();

private:
    Ui::DecomposeDialog *ui;
};

#endif // DECOMPOSEDIALOG_H
