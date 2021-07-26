#ifndef CARD_H
#define CARD_H
#include"include/pixmap.h"
#include<QString>
#include<QMap>
#include<QVector>

class Card:public Pixmap
{
public:
    Card(QString _name);
    const static QMap<QString, int> map;
    const static QVector<QString> name;
    const static QVector<int> cost;
    const static QVector<int> cool;
    void advance(int phase);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void resetCounter(){counter=0;}
    QString getName(){return plt_name;}
private:
    int counter;
    QString plt_name;
};

class Shovel:public Pixmap
{
public:
    Shovel();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void removePlant(QPointF p);
};


#endif // CARD_H
