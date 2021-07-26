#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QTimer>
#include <QSound>
#include "include/pixmap.h"

class ScoreBoard:public Pixmap
{
public:
    ScoreBoard();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class GameWidget:public Pixmap
{
public:
    GameWidget(QTimer *t);
    ~GameWidget();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
//    QSound *sound;
    QTimer *timer;
    ScoreBoard* board;
};

#endif // GAMEWIDGET_H
