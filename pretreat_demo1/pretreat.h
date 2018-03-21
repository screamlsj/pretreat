#ifndef PRETREAT_H
#define PRETREAT_H

#include <QMainWindow>

#include <QImage>

#include "HalconCpp.h"
#include "HDevThread.h"

#include "thesholdinputdialog.h"
#include "ui_thesholdinputdialog.h"


#include <QTime>
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>

using namespace HalconCpp;

namespace Ui {
class PreTreat;
}

class PreTreat : public QMainWindow
{
    Q_OBJECT

public:
    explicit PreTreat(QWidget *parent = 0);
    ~PreTreat();

   void showPicture(Ui::PreTreat*PT,QString filename);//这里也需要形参

    //QImage *image;
    int globalMark;
    QImage globalImg;
/**/

private slots:
    void on_OpenImageButton_clicked();

    void on_SaveImageButton_clicked();

    void on_LaplaceButton_clicked();

    void on_pushButton_clicked();

    void on_SobelButton_clicked();

    void on_SmoothButton_clicked();

    void on_ErosionButton_clicked();

    void on_DilationButton_clicked();

    void on_HighpassButton_clicked();

    void on_LowpassButton_clicked();

    void on_MedianpassButton_clicked();

    void on_thresholdButton_clicked();

private:
    Ui::PreTreat *ui;
    ThesholdInputDialog *tidialog;

};

#endif // PRETREAT_H
