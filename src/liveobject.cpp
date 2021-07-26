#include "liveobject.h"
#include<QDebug>

LiveObject::LiveObject():movie(nullptr),armor(0),demage(0),active_clk(20),counter(0)
{
}

LiveObject::~LiveObject()
{
    delete movie;
}

QRectF LiveObject::boundingRect() const
{
    if (movie)
        return movie->frameRect();
    else
        return QRectF(0,0,200,200);
}

void LiveObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawImage(boundingRect(), movie->currentImage());
}

void LiveObject::advance(int phase)
{
    Q_UNUSED(phase);
    update();
}

void LiveObject::reduceArmor(int x)
{
    armor-=x;
}

void LiveObject::resetMovie(QString path)
{
    if (movie)
        delete movie;
    movie = new QMovie(path);
    movie->start();
}
