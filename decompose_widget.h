#ifndef DECOMPOSE_WIDGET_H
#define DECOMPOSE_WIDGET_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QComboBox>
#include <QLabel>


class decompose_widget : public QWidget
{
    Q_OBJECT
public:
    explicit decompose_widget(QWidget *parent = nullptr);
    QComboBox *decompose_combobox;

signals:

public slots:
};

#endif // DECOMPOSE_WIDGET_H
