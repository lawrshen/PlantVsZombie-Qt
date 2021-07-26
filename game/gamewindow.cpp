#include "gamewindow.h"
#include "include/common.h"
#include <QPalette>
#include<QPixmap>
#include <QBrush>
#include <QIcon>
#include<QTime>
#include"gamewidget.h"
#include"src/liveobject.h"
#include"src/plants/plant.h"
#include"src/plants/sun.h"
#include"game/card.h"

ZombieVector gamewindow::zomComing[5] = {};
int gamewindow::sumScore=0;

gamewindow::gamewindow(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(game_windows[0],game_windows[1]);
    this->setWindowTitle("Plants vs Zombies (GUI) | By Shen Tianjie");
    this->setWindowIcon(QIcon(":/new/src/Icon/pvz_icon.png"));
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

//    sound = new QSound(":/new/src/Grazy Dave.mp3");
//    sound->setLoops(QSound::Infinite);
//    sound->play();

    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0, game_windows[0],game_windows[1]);

    garden = new Garden;
    garden->setPos(0,0);
    scene->addItem(garden);

    shop = new Shop;
    shop->setPos(0,0);
    scene->addItem(shop);

    Shovel* shovel=new Shovel;
    shovel->setPos(700,0);
    scene->addItem(shovel);

    for (int i = 0; i < 5; ++i){
        Car* car=new Car;
        car->setPos(180, plt_base.y()+i*obj_offset.y());
        scene->addItem(car);
    }

    view = new QGraphicsView(scene, this);
    view->setBackgroundBrush(QBrush(QPixmap(":/new/src/Garden/garden0.jpg")));
    view->show();

    timer=new QTimer;
    connect(timer,SIGNAL(timeout()),scene,SLOT(advance()));
    connect(timer,SIGNAL(timeout()),this,SLOT(addZombie()));
    connect(timer,SIGNAL(timeout()),this,SLOT(addSun()));
    connect(timer,SIGNAL(timeout()),this,SLOT(check()));
    timer->start(100);

    GameWidget *widget = new GameWidget(timer);
    widget->setPos(950, 0);
    scene->addItem(widget);
}

gamewindow::~gamewindow()
{
    delete scene;
    delete view;
    delete timer;
//    delete sound;
    delete shop;
    delete garden;
}

void gamewindow::addZombie()
{
    static int counter = 0,zom_refresh_time=80;
    if( ++counter > zom_refresh_time){
        zom_refresh_time=200;
        counter = 0;
        Zombie* zm=new NormalZombie;
        int zom_card = qrand() %6;
        if (qrand() % 10 > 2)
            zom_card = 0;
        switch (zom_card)
        {
        case NormalZombieCard:
            zm=new NormalZombie;
            break;
        case ConeheadZombieCard:
            zm=new ConeheadZombie;
            break;
        case NewspaperZombieCard:
            zm=new NewspaperZombie;
            break;
        case PoleVaultingZombieCard:
            zm = new PoleVaultingZombie;
            break;
        case JokerZombieCard:
            zm=new JokerZombie;
            break;
        case CatapultZombieCard:
            zm=new CatapultZombie;
            break;
        default:
            break;
        }
        int zom_y=qrand()%5;
        zm->setPos(zom_base.x(),zom_base.y()+zom_y*obj_offset.y());
        gamewindow::zomComing[zom_y].push_back(zm);
        scene->addItem(zm);
    }
}

void gamewindow::check()
{
    static int time = 30;
    static int counter = 0;
    if (++counter >= time)
    {
        counter = 0;
        const QList<QGraphicsItem *> items = scene->items();
        foreach (QGraphicsItem *item, items)
            if (item->type() == Zombie::Type && item->x() < 80)
            {
                scene->addPixmap(QPixmap(":/new/src/Screen/ZombiesWon.png"))->setPos(336, 92);
                scene->advance();
                timer->stop();
                return;
            }
    }
}

void gamewindow::addSun(){
    static int time = 300;
    static int counter = 0;
    if (++counter >= time)
    {
        counter = 0;
        Sun*s=new Sun(true);
        s->setPos(qrand()%600+200,60);
        scene->addItem(s);
    }
}
