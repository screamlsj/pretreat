#ifndef COMPAREDIALOG_H
#define COMPAREDIALOG_H

#include <QDialog>
#include <QFileDialog>

namespace Ui {
class CompareDialog;
}

class CompareDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CompareDialog(QWidget *parent = 0);
    ~CompareDialog();
    void getCompareInform(QString *,int *);

private slots:
    void on_pushButton_clicked();

private:
    Ui::CompareDialog *ui;
};

#endif // COMPAREDIALOG_H
