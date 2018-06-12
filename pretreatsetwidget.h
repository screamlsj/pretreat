#ifndef PRETREATSETWIDGET_H
#define PRETREATSETWIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>


class PretreatSetWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PretreatSetWidget(QWidget *parent = nullptr);
    QCheckBox *checkbox;
    QWidget *setparawidget,*hlayoutwidget;
    QPushButton *settingbutton;
//    QPushButton *testbutton;
//    QLabel *label;
    QHBoxLayout *hlayout;
    QVBoxLayout *vlayout;
    QVBoxLayout *setparawidgetlayout;
    void hideorshow();
signals:

public slots:

private:

};

#endif // PRETREATSETWIDGET_H
