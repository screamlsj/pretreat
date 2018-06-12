#ifndef MEDIAN_WIDGET_H
#define MEDIAN_WIDGET_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>

class median_widget :public QWidget
{
public:
    median_widget(QWidget *parent = nullptr);
    QComboBox *median_masktype_combobox;
    QComboBox *median_radius_combobox;
    QComboBox *median_margin_combobox;
};

#endif // MEDIAN_WIDGET_H
