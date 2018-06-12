#ifndef EROSIONANDDILATION_WIDGET_H
#define EROSIONANDDILATION_WIDGET_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QGridLayout>

class erosionanddilation_widget : public QWidget
{
    Q_OBJECT
public:
    explicit erosionanddilation_widget(QWidget *parent = nullptr);
    QComboBox *se_type_combobox;
    QComboBox *se_size_combobox;
signals:

public slots:
};

#endif // EROSIONANDDILATION_WIDGET_H
