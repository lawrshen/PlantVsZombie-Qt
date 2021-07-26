#include "pea.h"
#include "src/zombie.h"

Pea::Pea(int _demage,bool _snow):Pixmap(":/new/src/Pea/PeaNormal/PeaNormal_0.png"),demage(_demage),snow(_snow)
{
    if(_snow)
        pixmap.load(":/new/src/Pea/PeaIce/PeaIce_0.png");
}

void Pea::advance(int phase)
{
    Q_UNUSED(phase);
    update();
    QList<QGraphicsItem *> items = collidingItems();
   if (!items.isEmpty())
   {
       Zombie *zombie = qgraphicsitem_cast<Zombie *>(items[0]);
       zombie->reduceArmor(demage);
       if (snow && zombie->getSpeed() > 1)
           zombie->change_speed(zombie->getSpeed()/2);
       delete this;
       return;
   }
    setX(x()+15);
    if(x()>1200)
        delete this;
}

bool Pea::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode);
    return qFuzzyCompare(y()-other->y(),50) && qAbs(other->x() - x()) < 30;
}
