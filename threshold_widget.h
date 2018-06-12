#ifndef THRESHOLD_WIDGET_H
#define THRESHOLD_WIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QComboBox>
#include <QStackedWidget>
#include <QSpinBox>
#include <QLineEdit>
class threshold_widget : public QWidget
{
    Q_OBJECT
public:
    explicit threshold_widget(QWidget *parent = nullptr);


    QVBoxLayout *vlayout;
    QComboBox *combobox;
    QStackedWidget *stackedwidget;
    QWidget *thresholdpage;
    QWidget *dualthresholdpage;
    QWidget *varthresholdpage;
QSpinBox *mingray_spinBox ;
QSpinBox *maxgray_spinBox;
QLineEdit *dual_minsize_lineedit;
QSpinBox *dual_mingray_spinBox;
QSpinBox *dual_threshold_spinBox;

    QComboBox *var_masksize_combobox;
    QComboBox *var_stdDevScale_combobox;
    QComboBox *var_absThreshold_combobox;
    QComboBox *var_lightDark_combobox;

signals:

public slots:
    void switchpage(int index);

};

#endif // THRESHOLD_WIDGET_H
