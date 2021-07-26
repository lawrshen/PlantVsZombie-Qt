#include "zombie.h"
#include"plants/plant.h"
#include "include/common.h"
#include"game/gamewindow.h"
#include"game/shop.h"
#include<QTime>
#include<QDebug>

const int Zombie::zom_score[7] = { 10,20,20,30,30,50,10000 };

Zombie::Zombie():is_attacking(false),move_speed(0.9),z_card(NoneZomCard)
{

}

bool Zombie::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode);
    return other->type()==Plant::Type&&qFuzzyCompare(other->y()-y(),50) && qAbs(other->x() - x()) < 10;
}

void Zombie::delVector(bool dead)
{
    int line = (y()-zom_base.y())/obj_offset.y();
    ZombieVector &zv = gamewindow::zomComing[line];
    for(auto i=zv.begin();i<zv.end();i++){
        if(*i==this){
            if(dead)
                gamewindow::sumScore += zom_score[z_card];
            zv.erase(i);
            return;
        }
    }
}

NormalZombie::NormalZombie()
{
    armor=270;
    demage=100;
    active_clk = 20; 
    z_card = NormalZombieCard;
    movie = new QMovie(":/new/src/Zombies/NormalZombie/Zombie1.gif");
    movie->start();
}

void NormalZombie::advance(int phase){
    if (!phase)
        return;
    update();
    if(armor<=0){
        delVector();
        delete this;
        return;
    }
    QList<QGraphicsItem *> items = collidingItems();
    if (!items.isEmpty()){
        if(is_attacking==false)
            resetMovie(":/new/src/Zombies/NormalZombie/ZombieAttack.gif");
        is_attacking = true;
        if (++counter >= active_clk){
           counter = 0;
           Plant *plt = qgraphicsitem_cast<Plant *>(items[0]);
           plt->reduceArmor(demage);
        }
        return;
    }
    else{
        if(x()<0){
            //game over
            delete this;
        }
        else if(is_attacking){
            is_attacking=false;
            resetMovie(":/new/src/Zombies/NormalZombie/Zombie1.gif");
        }
        setX(x()-move_speed);
    }
}

ConeheadZombie::ConeheadZombie()
{
    armor=640;
    demage=100;
    active_clk = 20;
    z_card =ConeheadZombieCard;
    movie = new QMovie(":/new/src/Zombies/ConeheadZombie/ConeheadZombie.gif");
    movie->start();
}

void ConeheadZombie::advance(int phase){
    if (!phase)
        return;
    update();
    if(armor<=0){
        delVector();
        delete this;
        return;
    }
    QList<QGraphicsItem *> items = collidingItems();
    if (!items.isEmpty()){
        if(is_attacking==false)
            resetMovie(":/new/src/Zombies/ConeheadZombie/ConeheadZombieAttack.gif");
        is_attacking = true;
        if (++counter >= active_clk){
           counter = 0;
           Plant *plt = qgraphicsitem_cast<Plant *>(items[0]);
           plt->reduceArmor(demage);
        }
        return;
    }
    else{
        if(x()<0){
            //game over
            delete this;
        }
        else if(is_attacking){
            is_attacking=false;
            resetMovie(":/new/src/Zombies/ConeheadZombie/ConeheadZombie.gif");
        }
        setX(x()-move_speed);
    }
}

NewspaperZombie::NewspaperZombie()
{
    armor=420;
    demage=100;
    active_clk = 20;
    z_card =NewspaperZombieCard;
    faster = false;
    movie = new QMovie(":/new/src/Zombies/NewspaperZombie/HeadWalk1.gif");
    movie->start();
}

void NewspaperZombie::advance(int phase){
    if (!phase)
        return;
    update();
    if(armor<=0){
        delVector();
        delete this;
        return;
    }
    else if(armor<200 && !faster){
        change_speed(move_speed+0.3);
        faster=true;
        resetMovie(":/new/src/Zombies/NewspaperZombie/HeadWalk0.gif");
    }
    QList<QGraphicsItem *> items = collidingItems();
    if (!items.isEmpty()){
        if(is_attacking==false){
            if(armor<200)
                resetMovie(":/new/src/Zombies/NewspaperZombie/HeadAttack0.gif");
            else
                resetMovie(":/new/src/Zombies/NewspaperZombie/HeadAttack1.gif");
        }
        is_attacking = true;
        if (++counter >= active_clk){
           counter = 0;
           Plant *plt = qgraphicsitem_cast<Plant *>(items[0]);
           plt->reduceArmor(demage);
        }
        return;
    }
    else{
        if(x()<0){
            //game over
            delete this;
        }
        else if(is_attacking){
            is_attacking=false;
            if(armor<200)
                resetMovie(":/new/src/Zombies/NewspaperZombie/HeadWalk0.gif");
            else
                resetMovie(":/new/src/Zombies/NewspaperZombie/HeadWalk1.gif");
        }
        setX(x()-move_speed);
    }
}

PoleVaultingZombie::PoleVaultingZombie()
{
    armor=500;
    demage=100;
    active_clk = 20;
    move_speed = 3.3;
    z_card = PoleVaultingZombieCard;
    pole_state = 0;
    movie = new QMovie(":/new/src/Zombies/PoleVaultingZombie/PoleVaultingZombie.gif");
    movie->start();
}

void PoleVaultingZombie::advance(int phase){
    if (!phase)
        return;
    update();
    if(armor<=0){
        delVector();
        delete this;
        return;
    }
    if(pole_state==1){
        pole_state=2;
        resetMovie(":/new/src/Zombies/PoleVaultingZombie/PoleVaultingZombieWalk.gif");
        movie->start();
        update();
        return;
    }
    QList<QGraphicsItem *> items = collidingItems();
    if (!items.isEmpty()){
        Plant *plt = qgraphicsitem_cast<Plant *>(items[0]);
        if(pole_state==0&&plt->enable_jump){
            resetMovie(":/new/src/Zombies/PoleVaultingZombie/PoleVaultingZombieJump2.gif");
            pole_state = 1;
            setX(x()-130);
            change_speed(move_speed-2);
            return;
        }
        else if(pole_state==1){
            pole_state=2;
            resetMovie(":/new/src/Zombies/PoleVaultingZombie/PoleVaultingZombieWalk.gif");
            movie->start();
            update();
            return;
        }
        if(is_attacking==false)
            resetMovie(":/new/src/Zombies/PoleVaultingZombie/PoleVaultingZombieAttack.gif");
        is_attacking = true;
        if (++counter >= active_clk){
           counter = 0;
           plt->reduceArmor(demage);
        }
        return;
    }
    else{
        if(x()<0){
            //game over
            delete this;
        }
        else if(is_attacking){
            is_attacking=false;
            resetMovie(":/new/src/Zombies/PoleVaultingZombie/PoleVaultingZombieWalk.gif");
            movie->start();
        }
        setX(x()-move_speed);
    }
}

QRectF PoleVaultingZombie::boundingRect() const
{
    return QRectF(-20*1.8, -40*1.5, 200*1.8, 140*1.5);
}

bool PoleVaultingZombie::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode);
    if(pole_state==0)
        return other->type()==Plant::Type && qFuzzyCompare(other->y()-y(),50) && (other->x() - x()) > 100;
    else
        return other->type()==Plant::Type && qFuzzyCompare(other->y()-y(),50) && (other->x() - x()) > 100 && (other->x() - x()) < 140;
}

JokerZombie::JokerZombie()
{
    armor=500;
    demage=100;
    active_clk = 20;
    z_card = JokerZombieCard;
    begin_time = QTime(0,0,0).secsTo(QTime::currentTime());
    movie = new QMovie(":/new/src/Zombies/JokerZombie/Walk.gif");
    movie->start();
}

void JokerZombie::advance(int phase){
    if (!phase)
        return;
    update();
    if(armor<=0){
        delVector();
        delete this;
        return;
    }
    int bombprob = 100,rate=2;
    for(int i=0;i<5;i++)qrand();
    int prob = (qrand()-begin_time) % bombprob;
    prob = (prob + bombprob)%bombprob;
    int prate = (qrand()-begin_time) % bombprob;
    prate = (prate + bombprob)%bombprob;
    if ( prate > rate)
        prob = 0;
    if (prob > 0) {//bomb
        resetMovie(":/new/src/Zombies/JokerZombie/OpenBox.gif");

        Shop *shop = qgraphicsitem_cast<Shop *>(scene()->items(QPointF(0, 0))[0]);
        int j=(x()-plt_base.x())/obj_offset.x()-1,i=(y()-zom_base.y())/obj_offset.y()-1;
        int range = 3;//3 x 3
        for(int x=j;x<j+range;x++){
            for(int y=i;y<i+range;y++){
                int xx=x*obj_offset.x()+plt_base.x(),yy=y*obj_offset.y()+plt_base.y();
                if(shop->hasDefender(y,x)){
                    Plant *plt = qgraphicsitem_cast<Plant *>(scene()->items(QPointF(xx, yy))[0]);
                    plt->reduceArmor(demage*1000);
                    shop->clearDefender(y,x);
//                    Plant *pltt = qgraphicsitem_cast<Plant *>(scene()->items(QPointF(xx, yy))[1]);
//                    pltt->reduceArmor(demage*1000);
                }
                if(shop->hasOccupied(y,x)){
                    Plant *plt = qgraphicsitem_cast<Plant *>(scene()->items(QPointF(xx, yy))[0]);
                    plt->reduceArmor(demage*1000);
                    shop->clearOccupied(y,x);
                }
            }
        }
        delVector();
        delete this;
        return;
    }
    QList<QGraphicsItem *> items = collidingItems();
    if (!items.isEmpty()){
        if(is_attacking==false)
            resetMovie(":/new/src/Zombies/JokerZombie/Attack.gif");
        is_attacking = true;
        if (++counter >= active_clk){
           counter = 0;
           Plant *plt = qgraphicsitem_cast<Plant *>(items[0]);
           plt->reduceArmor(demage);
        }
        return;
    }
    else{
        if(x()<0){
            //game over

            delVector();
            delete this;
            return;
        }
        else if(is_attacking){
            is_attacking=false;
            resetMovie(":/new/src/Zombies/JokerZombie/Walk.gif");
        }
        setX(x()-move_speed);
    }
}

CatapultZombie::CatapultZombie()
{
    armor=850;
    demage=175;
    move_speed=0.6;
    active_clk = 50;
    z_card = CatapultZombieCard;
    stone_num = 7;
    movie = new QMovie(":/new/src/Zombies/CatapultZombie/1.gif");
    movie->start();
}

QRectF CatapultZombie::boundingRect() const
{
    return QRectF(0,-20, 360, 220);
}

void CatapultZombie::advance(int phase){
    if (!phase)
        return;
    update();
    if(armor<=0){
        delVector();
        delete this;
        return;
    }
    QList<QGraphicsItem *> items = collidingItems();
    if (!items.isEmpty()&&stone_num==0){
        if (++counter >= active_clk){
           counter = 0;
           Plant *plt = qgraphicsitem_cast<Plant *>(items[0]);
           plt->reduceArmor(demage*1000);
        }
        return;
    }
    else{
        if(x()<0){
            //game over
            delete this;
            return;
        }
        else if(++counter >= active_clk&&stone_num>0){
            counter = 0;
            Shop *shop = qgraphicsitem_cast<Shop *>(scene()->items(QPointF(0, 0))[0]);
            int j=(x()-plt_base.x())/obj_offset.x(),i=(y()-zom_base.y())/obj_offset.y();
            while(j>=0){
                if(shop->hasOccupied(i,j)){
                    stone_num--;
                    break;
                }
                j--;
            }
            if(j>=0){
                int xx=j*obj_offset.x()+plt_base.x(),yy=i*obj_offset.y()+plt_base.y();
                Plant *plt = qgraphicsitem_cast<Plant *>(scene()->items(QPointF(xx, yy))[0]);
                plt->reduceArmor(demage);
            }
        }
        else
            setX(x()-move_speed);
    }
}
