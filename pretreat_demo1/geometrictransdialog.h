#ifndef GEOMETRICTRANSDIALOG_H
#define GEOMETRICTRANSDIALOG_H

#include <QDialog>

namespace Ui {
class GeometricTransDialog;
}

class GeometricTransDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GeometricTransDialog(QWidget *parent = 0);
    ~GeometricTransDialog();
    void getcutIndex(int *,int *,int *,int *);

private:
    Ui::GeometricTransDialog *ui;
};

#endif // GEOMETRICTRANSDIALOG_H
