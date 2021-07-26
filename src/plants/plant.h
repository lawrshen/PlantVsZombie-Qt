#ifndef PALNT_H
#define PALNT_H
#include"src/liveobject.h"


class Plant:public LiveObject
{
public:
    Plant();
    bool ZombieComing(QPointF p);
    enum { Type = UserType + 3 };
    int type() const{ return Type;}
    bool enable_jump;
protected:
    int sun;
};

class SunFlower:public Plant
{
public:
    SunFlower();
    void advance(int phase);
};

class Peashooter:public Plant
{
public:
    Peashooter();
    void advance(int phase);
};

class Repeater:public Plant
{
public:
    Repeater();
    void advance(int phase);
};

class SnowPea : public Plant
{
public:
    SnowPea();
    void advance(int phase);
};

class WallNut: public Plant
{
public:
    WallNut();
    void advance(int phase);
private:
    int state;
};

class TallNut : public Plant
{
public:
    TallNut();
    void advance(int phase);
    QRectF boundingRect() const;
private:
    int state;
};

class Squash :public Plant
{
public:
    Squash();
    void advance(int phase);
    QRectF boundingRect() const;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const;
};

class Cherrybomb :public Plant
{
public:
    Cherrybomb();
    void advance(int phase);
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const;
};

class Garlic :public Plant
{
    bool atked;
    int state;
public:
    Garlic();
    void advance(int phase);
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const;
    void reduceArmor(int x);
};

class Pumpkin :public Plant
{
    int state;
public:
    Pumpkin();
    void advance(int phase);
};

#endif // PALNT_H
