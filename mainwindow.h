#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "pretreatdialog.h"
#include "ui_pretreatdialog.h"
#include "showimage.h"


#include <QMainWindow>
#include "HalconCpp.h"
#include "HDevThread.h"
#include <QImage>
#include <QMouseEvent>
#include <QTime>
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>

#include "sysfile.h"


#include <QDebug>
#include <sys/time.h>

extern HObject ho_Image;

using namespace HalconCpp;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_openImage_action_triggered();
    void mouseMoveEvent(QMouseEvent *);
    void showPicture(QImage*);

    void on_pretreat_pushButton_clicked();

    void on_dopretreat_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    PreTreatDialog *prtredialog;

};

#endif // MAINWINDOW_H
