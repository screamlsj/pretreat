#ifndef THESHOLDINPUTDIALOG_H
#define THESHOLDINPUTDIALOG_H

#include <QDialog>

namespace Ui {
class ThesholdInputDialog;
}

class ThesholdInputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ThesholdInputDialog(QWidget *parent = 0);
    ~ThesholdInputDialog();
int getMaxGray();
int getMinGray();
int getForegroundGray();
int getBackgroundGray();

private:
    Ui::ThesholdInputDialog *ui;
};

#endif // THESHOLDINPUTDIALOG_H
