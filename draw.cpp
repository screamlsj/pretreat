#include "draw.h"
#include <QGroupBox>
#include <QVBoxLayout>
draw::draw(QWidget *parent)
    :QToolBox(parent)
{
    toolBtn1_1=new QToolButton;
    toolBtn1_1->setText(tr("张三"));
    toolBtn1_1->setAutoRaise(1);

    QGroupBox *groupBox1=new QGroupBox;
    QVBoxLayout *layout1=new QVBoxLayout(groupBox1);
     layout1->addWidget(toolBtn1_1);

     QGroupBox *groupBox2=new QGroupBox;
    QGroupBox *groupBox3=new QGroupBox;

    this->addItem((QWidget*)groupBox1,tr("我的好友"));
   this->addItem((QWidget*)groupBox2,tr("陌生人"));
   this->addItem((QWidget*)groupBox3,tr("黑名单"));

}
