#include "pretreatsetwidget.h"
#include <QDebug>

PretreatSetWidget::PretreatSetWidget(QWidget *parent)
    : QWidget(parent)
{

    checkbox = new QCheckBox;
    settingbutton=new QPushButton;

    checkbox->setText("checkbox");
    settingbutton->setText("setting");

//    checkbox->setFixedSize(150,30);
//    settingbutton->setFixedSize(50,30);
    checkbox->setMinimumWidth(200);

    hlayout=new QHBoxLayout;
    vlayout=new QVBoxLayout;

    hlayout->addWidget(checkbox);
    hlayout->addWidget(settingbutton);

    hlayoutwidget=new QWidget;
    hlayoutwidget->setLayout(hlayout);

    hlayoutwidget->setFixedSize(250,40);

    vlayout->addWidget(hlayoutwidget);

    setparawidget=new QWidget;
//    label=new QLabel(setparawidget);
//    label->setText("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\nbbbbbb");

//    testbutton=new QPushButton;
//    testbutton->setText("ttttttttttt");

    QPalette pal(setparawidget->palette());
    pal.setColor(QPalette::Background, Qt::yellow);
    setparawidget->setAutoFillBackground(true);
    setparawidget->setPalette(pal);

    setparawidgetlayout=new QVBoxLayout;
//    setparawidgetlayout->addWidget(testbutton);

    setparawidget->setLayout(setparawidgetlayout);

     // setparawidget->setVisible(false);
    this->setparawidget->hide();



    vlayout->addWidget(setparawidget);

    vlayout->setContentsMargins(0,0,0,0);
    vlayout->setSpacing(0);

    this->setLayout(vlayout);
//    this->setMaximumWidth(200);
//    this->setMinimumWidth(190);
    qDebug() << this->sizeHint().width() << "," << this->sizeHint().height();
    this->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    connect(this->settingbutton,&QPushButton::clicked,this,&PretreatSetWidget::hideorshow);

}

void PretreatSetWidget::hideorshow()
{
    if(setparawidget->isVisible())
    {
        this->setparawidget->hide();
    }
    else
    {
        this->setparawidget->show();
    }
}




