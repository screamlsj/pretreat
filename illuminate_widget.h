#ifndef ILLUMINATE_WIDGET_H
#define ILLUMINATE_WIDGET_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QComboBox>
#include <QLabel>

class illuminate_widget : public QWidget
{
    Q_OBJECT
public:
    explicit illuminate_widget(QWidget *parent = nullptr);
    QComboBox *illuminate_masksize_combobox;
    QComboBox *illuminate_factor_combobox;
signals:

public slots:
};

#endif // ILLUMINATE_WIDGET_H
