#ifndef EMPHASIZE_WIDGET_H
#define EMPHASIZE_WIDGET_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QComboBox>
#include <QLabel>
class emphasize_widget  :public QWidget
{
public:
    emphasize_widget(QWidget *parent = nullptr);
    QComboBox *emphasize_masksize_combobox;
    QComboBox *emphasize_factor_combobox;
};

#endif // EMPHASIZE_WIDGET_H
