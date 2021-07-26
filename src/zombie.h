#ifndef ZOMBIE_H
#define ZOMBIE_H
#include"src/liveobject.h"
#include"include/common.h"
class Zombie:public LiveObject
{
public:
    Zombie();
    virtual bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const;
    int getSpeed()const {return move_speed;}
    void change_speed(int val){move_speed=val;}
    void delVector(bool dead=true);
    enum { Type = UserType + 2 };
    int type() const{ return Type;}
    const static int zom_score[7] ;
protected:
    ZombieCard z_card;
    bool is_attacking;
    qreal move_speed;
};

typedef QVector<Zombie *> ZombieVector;

class NormalZombie : public Zombie
{
public:
    NormalZombie();
    void advance(int phase);
};

class ConeheadZombie: public Zombie
{
public:
    ConeheadZombie();
    void advance(int phase);
};

class NewspaperZombie: public Zombie
{
    bool faster;
public:
    NewspaperZombie();
    void advance(int phase);
};

class PoleVaultingZombie: public Zombie
{
    int pole_state;
public:
    PoleVaultingZombie();
    void advance(int phase);
    QRectF boundingRect() const;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const;
};

class JokerZombie: public Zombie
{
public:
    JokerZombie();
    void advance(int phase);
private:
    int begin_time;
};

class CatapultZombie: public Zombie
{
    int stone_num;
public:
    CatapultZombie();
    void advance(int phase);
    QRectF boundingRect() const;
};

#endif // ZOMBIE_H
