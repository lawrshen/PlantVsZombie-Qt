#include "card.h"
#include "shop.h"
#include<QGraphicsSceneEvent>
#include<QDrag>
#include<QMimeData>
#include<QImage>
#include<QApplication>
#include"src/plants/plant.h"
#include"include/common.h"

const QMap<QString, int> Card::map = {{"SunFlower", 0}, {"Peashooter", 1}, {"SnowPea", 2}, {"Repeater", 3},{"WallNut", 4},
                                      {"TallNut", 5}, {"Cherrybomb", 6}, {"Squash",7},{"Garlic",8},{"Pumpkin",9}};
const QVector<QString> Card::name = {"SunFlower", "Peashooter","SnowPea","Repeater","WallNut",
                                     "TallNut", "Cherrybomb", "Squash","Garlic","Pumpkin"};
const QVector<int> Card::cost = {50, 100, 175, 200, 50, 125, 150 , 50, 50,125};
const QVector<int> Card::cool = {120, 120, 160, 160, 160, 160, 160, 260, 100, 606};

Card::Card(QString _name):Pixmap(":/new/src/Cards/card_"+_name+".png"),plt_name(_name),counter(0)
{

}

void Card::advance(int phase)
{
    if (!phase)
        return;
    update();
    if (counter < cool[map[plt_name]])
        ++counter;
}

void Card::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawPixmap(0,0,pixmap);
    if (counter < cool[map[plt_name]])
    {
        QBrush brush(QColor(0, 0, 0, 200));
        painter->setBrush(brush);
        painter->drawRect(QRectF(0,0,pixmap.width(), pixmap.height() * (1 - qreal(counter) / cool[map[plt_name]])));
    }
}

void Card::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    if (counter < cool[map[plt_name]])
        event->setAccepted(false);
    Shop *shop = qgraphicsitem_cast<Shop *>(parentItem());
    if (cost[map[plt_name]] > shop->getSun())
        event->setAccepted(false);
    setCursor(Qt::ArrowCursor);
}

void Card::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    QDrag *drag = new QDrag(event->widget());
    QMimeData *mime = new QMimeData;
    QImage image(":/new/src/Cards/"+plt_name+".gif");
    mime->setText(plt_name);
    mime->setImageData(image);
    drag->setMimeData(mime);
    drag->setPixmap(QPixmap::fromImage(image));
    drag->setHotSpot(QPoint(35, 35));
    drag->exec();
    setCursor(Qt::ArrowCursor);
}

void Card::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    setCursor(Qt::ArrowCursor);
}

Shovel::Shovel():Pixmap(":/new/src/Screen/shovelSlot.png"){}

void Shovel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawPixmap(0,0, QPixmap(":/new/src/Screen/shovelSlot.png"));
    painter->drawPixmap(0,0, QPixmap(":/new/src/Screen/shovel.png"));
}

void Shovel::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    setCursor(Qt::ArrowCursor);
}

void Shovel::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    QDrag *drag = new QDrag(event->widget());
    QMimeData *mime = new QMimeData;
    QImage image(":/new/src/Screen/shovel.png");
    mime->setText("Shovel");
    mime->setImageData(image);
    drag->setMimeData(mime);
    drag->setPixmap(QPixmap::fromImage(image));
    drag->setHotSpot(QPoint(35, 35));
    drag->exec();
    setCursor(Qt::ArrowCursor);
}

void Shovel::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    setCursor(Qt::ArrowCursor);
}

void Shovel::removePlant(QPointF p)
{
    int j=(p.x()-plt_base.x())/obj_offset.x(),i=(p.y()-plt_base.y())/obj_offset.y();
    Shop *shop = qgraphicsitem_cast<Shop *>(scene()->items(QPointF(0, 0))[0]);
    if(shop->hasOccupied(i,j)){
         QList<QGraphicsItem *> items = scene()->items(p);
         foreach (QGraphicsItem *item, items)
            if (item->type() == Plant::Type)
                delete item;
    }
}
