#ifndef LIVEOBJECT_H
#define LIVEOBJECT_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include<QPainter>
#include<QMovie>
#include<QPoint>

class LiveObject:public QGraphicsItem
{
public:
    LiveObject();
    ~LiveObject();
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual void advance(int phase);
    virtual void reduceArmor(int x);
    void resetMovie(QString path);
    enum { Type = UserType + 1 };
    int type() const{ return Type;}
protected:
    QMovie* movie;
    int armor;
    int demage;
    int active_clk;
    int counter;
};

#endif // LIVEOBJECT_H
