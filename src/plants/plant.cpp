#include "plant.h"
#include"src/zombie.h"
#include"sun.h"
#include"pea.h"
#include"include/common.h"
#include"game/shop.h"
#include"game/gamewindow.h"
#include<QTime>

Plant::Plant():sun(0),enable_jump(true)
{
    armor = 300;
    active_clk = 30;
}

bool Plant::ZombieComing(QPointF p)
{
    int line = (p.y()-plt_base.y())/obj_offset.y();
    ZombieVector &zv = gamewindow::zomComing[line];
    if (zv.size() == 0)
        return false;
    auto i = zv.begin();
    Zombie *firstZombie = *i;
    for (i=i+1; i<zv.end(); i++){
        if (firstZombie->pos().x() > (*i)->pos().x())
            firstZombie = *i;
    }
    return p.x()<firstZombie->x();
}

SunFlower::SunFlower()
{
    active_clk = 160;
    movie = new QMovie(":/new/src/Plants/SunFlower/1.gif");
    movie->start();
}

void SunFlower::advance(int phase)
{
    update();
    if(!phase){
        if (armor <= 0){
            Shop *shop = qgraphicsitem_cast<Shop *>(scene()->items(QPointF(0, 0))[0]);
            shop->refreshPlant(pos());
            delete this;
        }
        else if (++counter >= active_clk)
        {
            counter = 0;
            Sun*s=new Sun;
            s->setPos(x()+10,y()+20);
            scene()->addItem(s);
        }
    }
}

Peashooter::Peashooter()
{
    demage = 20;
    movie=new QMovie(":/new/src/Plants/Peashooter/1.gif");
    movie->start();
}

void Peashooter::advance(int phase){
    update();
    if(!phase){
        if (armor <= 0){
            Shop *shop = qgraphicsitem_cast<Shop *>(scene()->items(QPointF(0, 0))[0]);
            shop->refreshPlant(pos());
            delete this;
        }
        else if (++counter >= active_clk){
            counter = 0;
            if(ZombieComing(pos())){
                Pea* p=new Pea(demage);
                p->setPos(x()+obj_offset.x(),y());
                scene()->addItem(p);
            }
        }
    }
}

Repeater::Repeater()
{
    demage = 20;
    movie = new QMovie(":/new/src/Plants/Repeater/1.gif");
    movie->start();
}

void Repeater::advance(int phase){
    update();
    if(!phase){
        if (armor <= 0){
            Shop *shop = qgraphicsitem_cast<Shop *>(scene()->items(QPointF(0, 0))[0]);
            shop->refreshPlant(pos());
            delete this;
        }
        else if (++counter >= active_clk){
            counter = 0;
            if(ZombieComing(pos())){
                Pea* p[2];
                for(int i=0;i<2;i++){
                    p[i]=new Pea(demage);
                    p[i]->setPos(x()+obj_offset.x()+i*25,y());
                    scene()->addItem(p[i]);
                }
            }
        }
    }
}

SnowPea::SnowPea()
{
    demage=20;
    movie=new QMovie(":/new/src/Plants/SnowPea/1.gif");
    movie->start();
}

void SnowPea::advance(int phase){
    update();
    if(!phase){
        if (armor <= 0){
            Shop *shop = qgraphicsitem_cast<Shop *>(scene()->items(QPointF(0, 0))[0]);
            shop->refreshPlant(pos());
            delete this;
        }
        else if (++counter >= active_clk){
            counter = 0;
            if(ZombieComing(pos())){
                Pea* p=new Pea(demage,true);
                p->setPos(x()+obj_offset.x(),y());
                scene()->addItem(p);
            }
        }
    }
}

WallNut::WallNut()
{
    state = 0;
    armor = 4000;
    movie = new QMovie(":/new/src/Plants/WallNut/1.gif");
    movie->start();
}

void WallNut::advance(int phase){
    if(!phase){
        update();
        if (armor <= 0){
            Shop *shop = qgraphicsitem_cast<Shop *>(scene()->items(QPointF(0, 0))[0]);
            shop->refreshPlant(pos());
            delete this;
        }
        else if(armor<=1000&&state==1){
            resetMovie(":/new/src/Plants/WallNut/Wallnut_cracked2.gif");
            state=2;
        }
        else if(armor<=2500&&state==0){
            resetMovie(":/new/src/Plants/WallNut/Wallnut_cracked1.gif");
            state=1;
        }
    }
}

TallNut::TallNut()
{
    state = 0;
    armor = 8000;
    enable_jump = false;
    movie = new QMovie(":/new/src/Plants/TallNut/TallNut.gif");
    movie->start();
}

QRectF TallNut::boundingRect() const
{
    return QRectF(0,0, 70, 100);
}

void TallNut::advance(int phase){
    update();
    if(!phase){
        if (armor <= 0){
            Shop *shop = qgraphicsitem_cast<Shop *>(scene()->items(QPointF(0, 0))[0]);
            shop->refreshPlant(pos());
            delete this;
        }
        else if(armor<=1000&&state==1){
            resetMovie(":/new/src/Plants/TallNut/TallnutCracked2.gif");
            state=2;
        }
        else if(armor<=2500&&state==0){
            resetMovie(":/new/src/Plants/TallNut/TallnutCracked1.gif");
            state=1;
        }
    }
}

Squash::Squash()
{
    sun = 50;
    demage = 100000;
    movie = new QMovie(":/new/src/Plants/Squash/1.gif");
    movie->start();
}

void Squash::advance(int phase){
    update();
    if(!phase){
        if (armor <= 0){
            Shop *shop = qgraphicsitem_cast<Shop *>(scene()->items(QPointF(0, 0))[0]);
            shop->refreshPlant(pos());
            delete this;
        }
        else{
             QList<QGraphicsItem *> items = collidingItems();
            if(!items.empty()){
                Zombie* zom = qgraphicsitem_cast<Zombie *>(items[0]);
                zom->reduceArmor(demage);
                Shop *shop = qgraphicsitem_cast<Shop *>(scene()->items(QPointF(0, 0))[0]);
                shop->refreshPlant(pos());
                delete this;
            }
        }
    }
}

QRectF Squash::boundingRect() const
{
    return QRectF(-10,-130, 100, 210);
}

bool Squash::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode);
    return other->type()==Zombie::Type&&qFuzzyCompare(y()-other->y(),50) && qAbs(other->x() - x()) < 20;
}

Cherrybomb::Cherrybomb()
{
    active_clk = 6;
    demage = 100000;
    movie = new QMovie(":/new/src/Plants/CherryBomb/1.gif");
    movie->start();
}

bool Cherrybomb::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode);
    return other->type()==Zombie::Type&& (
                (other->y()>y() && (other->y() - y()) < 43 ) ||
                (y()>other->y() && (y() - other->y()) < 143 ) )
                && (other->x() - x() < 180||x()-other->x()< 80);
}

void Cherrybomb::advance(int phase){
    update();
    if(!phase){
        if (armor <= 0){
            Shop *shop = qgraphicsitem_cast<Shop *>(scene()->items(QPointF(0, 0))[0]);
            shop->refreshPlant(pos());
            delete this;
        }
    }
    else if (++counter >= active_clk){
       QList<QGraphicsItem *> items = collidingItems();
       resetMovie(":/new/src/Plants/CherryBomb/Boom.gif");
       movie->start();
       update();
       if(!items.empty()){
           for(int i=0;i<items.size();i++){
               Zombie* zom = qgraphicsitem_cast<Zombie *>(items[i]);
               zom->reduceArmor(demage);
           }
       }
       Shop *shop = qgraphicsitem_cast<Shop *>(scene()->items(QPointF(0, 0))[0]);
       shop->refreshPlant(pos());
       delete this;
    }
}

Garlic::Garlic()
{
    state = 0;
    atked = false;
    movie = new QMovie(":/new/src/Plants/Garlic/Garlic.gif");
    movie->start();
}

void Garlic::advance(int phase){
    update();
    if(!phase){
        if (armor <= 0){
            Shop *shop = qgraphicsitem_cast<Shop *>(scene()->items(QPointF(0, 0))[0]);
            shop->refreshPlant(pos());
            delete this;
            return;
        }
        else if(armor<=200&&state==1){
            resetMovie(":/new/src/Plants/Garlic/Garlic_body2.gif");
            state=2;
        }
        else if(armor<=100&&state==0){
            resetMovie(":/new/src/Plants/Garlic/Garlic_body3.gif");
            state=1;
        }

       QList<QGraphicsItem *> items = collidingItems();
       if(!items.empty()&&atked){
           atked=false;
           Zombie* zom = qgraphicsitem_cast<Zombie *>(items[0]);
            qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
            bool upflag=false;
            int zom_y = (y()-zom_base.y())/obj_offset.y();
            zom->delVector(false);
            if(qrand()%2==0){
                if(zom->y()-obj_offset.y() < zom_base.y())
                    zom->setPos(zom->x(),zom->y()+obj_offset.y());
                else{
                    zom->setPos(zom->x(),zom->y()-obj_offset.y());
                    upflag=true;
                }
            }
            else{
                if(zom->y() == 4*obj_offset.y() + zom_base.y()){
                    zom->setPos(zom->x(),zom->y()-obj_offset.y());
                    upflag=true;
                }
                else
                    zom->setPos(zom->x(),zom->y()+obj_offset.y());
            }
            if(upflag){
                zom_y--;
                gamewindow::zomComing[zom_y].push_back(zom);
            }
            else{
                zom_y++;
                gamewindow::zomComing[zom_y].push_back(zom);
            }
       }

    }
}

void Garlic::reduceArmor(int x)
{
    if(atked==false)
        atked=true;
    armor-=x;
}

bool Garlic::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode);
    return other->type()==Zombie::Type&&qFuzzyCompare(y()-other->y(),50) && qAbs(other->x() - x()) < 20;
}

Pumpkin::Pumpkin()
{
    armor= 4000;
    state = 0;
    movie = new QMovie(":/new/src/Plants/Pumpkin/Pumpkin.gif");
    movie->start();
}

void Pumpkin::advance(int phase){
    update();
    if(!phase){
        if (armor <= 0){
            Shop *shop = qgraphicsitem_cast<Shop *>(scene()->items(QPointF(0, 0))[0]);
            shop->refreshPumpkin(pos());
            delete this;
        }
        else if(armor<=1000&&state==1){
            resetMovie(":/new/src/Plants/Pumpkin/pumpkin2.gif");
            state=2;
        }
        else if(armor<=2500&&state==0){
            resetMovie(":/new/src/Plants/Pumpkin/pumpkin1.gif");
            state=1;
        }
    }
}
