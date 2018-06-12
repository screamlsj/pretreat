#ifndef SCALEIMAGE_WIDGET_H
#define SCALEIMAGE_WIDGET_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QSlider>

class scaleimage_widget : public QWidget
{
    Q_OBJECT
public:
    explicit scaleimage_widget(QWidget *parent = nullptr);
    QLineEdit *scaleimage_mult_lineedit;
    QSpinBox *scaleimage_add_spinbox;
signals:

public slots:
};

#endif // SCALEIMAGE_WIDGET_H
