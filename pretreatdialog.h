#ifndef PRETREATDIALOG_H
#define PRETREATDIALOG_H

#include <QDialog>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QImage>
#include <QMessageBox>
#include <QString>
#include <string>
#include <QDebug>
using namespace std;

#include "pretreatsetwidget.h"
#include "threshold_widget.h"
#include "decompose_widget.h"
#include "illuminate_widget.h"
#include "scaleimage_widget.h"
#include "erosionanddilation_widget.h"
#include "mean_widget.h"
#include "emphasize_widget.h"
#include "median_widget.h"

#include "HalconCpp.h"
#include "HDevThread.h"
#include "showimage.h"
#include "sysfile.h"


namespace Ui {
class PreTreatDialog;
}

class PreTreatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PreTreatDialog(QWidget *parent = 0);
    ~PreTreatDialog();
    QPushButton *testbutton;
    QLabel *label;
  static HObject previewImage;
  void setDefaultPara();
  void saveDefaultPara();
  void pretreatImage(HObject *himage);

private slots:
    void on_previewpushButton_clicked();

private:
    void initSelectwidget();


private:
    void showPicture(QImage *qimage);

    Ui::PreTreatDialog *ui;
    QScrollArea *m_selectScrollArea;
        QVBoxLayout* m_VLayout;
      PretreatSetWidget  *presetwidget;
      PretreatSetWidget *threshold_presetwidget;
        threshold_widget *thresholdwidget;
      PretreatSetWidget *decompose_presetwidget;
        decompose_widget *decomposewidget;
      PretreatSetWidget *illuminate_presetwidget;
        illuminate_widget *illuminatewidget;
      PretreatSetWidget *scaleimage_presetwidget;
        scaleimage_widget *scaleimagewidget;
      PretreatSetWidget *erosion_presetwidget;
        erosionanddilation_widget *erosionwidget;
      PretreatSetWidget *dilation_presetwidget;
        erosionanddilation_widget *dilationwidget;
      PretreatSetWidget *opening_presetwidget;
        erosionanddilation_widget *openingwidget;
      PretreatSetWidget *closing_presetwidget;
        erosionanddilation_widget *closingwidget;
      PretreatSetWidget *mean_presetwidget;
        mean_widget *meanwidget;
      PretreatSetWidget *emphasize_presetwidget;
        emphasize_widget *emphasizewidget;
      PretreatSetWidget *median_presetwidget;
        median_widget *medianwidget;
};

#endif // PRETREATDIALOG_H
