#include "sun.h"
#include "game/shop.h"
#include<QGraphicsSceneEvent>

Sun::Sun(bool _env):counter(0),active_clk(50),is_env(_env)
{
    movie = new QMovie(":/new/src/Screen/Sun.gif");
    movie->start();
}

Sun::~Sun()
{
    delete movie;
}

QRectF Sun::boundingRect() const
{
    if (movie)
        return movie->frameRect();
    else
        return QRectF();
}

void Sun::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawImage(boundingRect(), movie->currentImage());
}

void Sun::advance(int phase)
{
    Q_UNUSED(phase);
    update();
    if(is_env){
        setY(y()+1);
        if(y()>650||counter==active_clk)
            delete this;
    }
    else if (++counter >= active_clk)
        delete this;
}

void Sun::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Shop *shop = qgraphicsitem_cast<Shop *>(scene()->items(QPointF(0, 0))[0]);
    shop->addSun(25);
    counter = active_clk;
    event->setAccepted(true);
}
