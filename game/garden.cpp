#include "garden.h"
#include<QGraphicsView>
#include<QMimeData>
#include"shop.h"
#include"card.h"
#include"include/common.h"
#include"src/zombie.h"

Garden::Garden():Pixmap(":/new/src/Garden/garden0.jpg")
{
    dragOver = false;
    setAcceptDrops(true);
}

void Garden::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    Q_UNUSED(painter);
}

void Garden::dragEnterEvent(QGraphicsSceneDragDropEvent *event){
    if (event->mimeData()->hasText()){
       event->setAccepted(true);
       dragOver = true;
       update();
    }
    else
       event->setAccepted(false);
}

void Garden::dragLeaveEvent(QGraphicsSceneDragDropEvent *event){
    Q_UNUSED(event);
    dragOver = false;
    update();
}

void Garden::dropEvent(QGraphicsSceneDragDropEvent *event){
    dragOver = false;
    if (event->mimeData()->hasText())
    {
        QString name = event->mimeData()->text();
        QPointF p = mapToScene(event->pos().toPoint());
        p.setX((int(p.x() - plt_base.x())) / obj_offset.x() * obj_offset.x() + plt_base.x());
        p.setY((int(p.y() - plt_base.y())) / obj_offset.y() * obj_offset.y() + plt_base.y());
        if (name == "Shovel")
        {
            Shovel *shovel = qgraphicsitem_cast<Shovel *>(scene()->items(QPointF(700, 0))[0]);
            shovel->removePlant(p);
        }
        else
        {
            Shop *shop = qgraphicsitem_cast<Shop *>(scene()->items(QPointF(0, 0))[0]);
            shop->addPlant(name, p);
        }
    }
    update();
}

Car::Car():Pixmap(":/new/src/Screen/car.png"){
    move_speed = 8;
    flag=false;
}

bool Car::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const{
    Q_UNUSED(mode)
    return other->type() == Zombie::Type && qFuzzyCompare(y()-other->y(), 50) && qAbs(other->x() - x()) < 15;
}


void Car::advance(int phase){
    if (!phase)
        return;
    update();
    QList<QGraphicsItem *> items = collidingItems();
    if (!items.empty())
    {
        flag = true;
        foreach (QGraphicsItem *item, items)
        {
            Zombie *zombie = qgraphicsitem_cast<Zombie *>(item);
            zombie->reduceArmor(100000);
        }
    }
    if (flag)
        setX(x() + move_speed);
    if (x() > 1000)
        delete this;
}
