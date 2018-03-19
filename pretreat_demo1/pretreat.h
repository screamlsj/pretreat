#ifndef PRETREAT_H
#define PRETREAT_H

#include <QMainWindow>

#include <QImage>

#include "HalconCpp.h"
#include "HDevThread.h"

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

private:
    Ui::PreTreat *ui;
};

#endif // PRETREAT_H
