#ifndef MEAN_WIDGET_H
#define MEAN_WIDGET_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>

class mean_widget :public QWidget
{
public:
    explicit mean_widget(QWidget *parent = nullptr);
    QComboBox *mean_masksize_combobox;

};

#endif // MEAN_WIDGET_H
