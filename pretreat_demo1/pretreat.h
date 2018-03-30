#ifndef PRETREAT_H
#define PRETREAT_H

#include <QMainWindow>

#include <QImage>

#include "HalconCpp.h"
#include "HDevThread.h"

#include "thesholdinputdialog.h"
#include "ui_thesholdinputdialog.h"
#include "scaleinputdialog.h"
#include "ui_scaleinputdialog.h"
#include "decomposedialog.h"
#include "ui_decomposedialog.h"
#include "geometrictransdialog.h"
#include "ui_geometrictransdialog.h"
#include "affinetransdialog.h"
#include "ui_affinetransdialog.h"
#include "comparedialog.h"
#include "ui_comparedialog.h"
#include "emphasizedialog.h"
#include "ui_emphasizedialog.h"
#include "scalemaxdialog.h"
#include "ui_scalemaxdialog.h"
#include "illuminatedialog.h"
#include "ui_illuminatedialog.h"

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

    void on_ScaleButton_clicked();


    void on_DecomposeButton_clicked();

    void on_GeoTransButton_clicked();

    void on_affineTranspushButton_clicked();

    void on_CompareButton_clicked();

    void on_EmphasizeButton_clicked();

    void on_scale_max_pushButton_clicked();

    void on_illuminatepushButton_clicked();

private:
    Ui::PreTreat *ui;
    ThesholdInputDialog *tidialog;
    ScaleInputDialog *sidialog;
    DecomposeDialog *dcDialog;
    GeometricTransDialog *gtdialog;
    AffineTransDialog *aftdialog;
    CompareDialog *cpdialog;
    EmphasizeDialog *epdialog;
    ScaleMaxDialog *smdialog;
    IlluminateDialog *ildialog;
};

#endif // PRETREAT_H
