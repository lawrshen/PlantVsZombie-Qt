#ifndef GARDEN_H
#define GARDEN_H
#include "include/pixmap.h"
#include <QGraphicsSceneDragDropEvent>

class Garden: public Pixmap
{
public:
    Garden();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);
private:
    bool dragOver;
};

class Car:public Pixmap
{
public:
    Car();
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const;
    void advance(int phase);
private:
    bool flag;
    qreal move_speed;
};

#endif // GARDEN_H
