#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include<QSound>
#include"shop.h"
#include"garden.h"
#include"src/zombie.h"

class gamewindow : public QWidget
{
    Q_OBJECT
public:
    explicit gamewindow(QWidget *parent = 0);
    ~gamewindow();

    static ZombieVector zomComing[5];
    static int sumScore;
private:
    QGraphicsScene* scene;
    QGraphicsView* view;
    QTimer* timer;
//    QSound *sound;
    Shop* shop;
    Garden* garden;

signals:

public slots:
    void addZombie();
    void addSun();
    void check();
};

#endif // GAMEWINDOW_H
