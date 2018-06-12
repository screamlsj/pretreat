#ifndef DRAW_H
#define DRAW_H

 #include <QToolBox>
 #include <QToolButton>
class draw : public QToolBox
{

    Q_OBJECT

public:
    draw(QWidget *parent=0);
private:
   QToolButton *toolBtn1_1;
};

#endif // DRAW_H
