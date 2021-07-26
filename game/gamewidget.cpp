#include "gamewidget.h"
#include<QGraphicsSceneEvent>
#include"gamewindow.h"
#include<QString>
GameWidget::GameWidget(QTimer *t):Pixmap(":/new/src/Screen/GameWidget.png"),timer(t),board(nullptr){}

GameWidget::~GameWidget(){
//    delete sound;
    delete timer;
    delete board;
}

void GameWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawPixmap(0,0,pixmap);
    painter->setPen(Qt::green);
    QFont font("Calibri", 14, QFont::Bold, true);
    painter->setFont(font);
    if (timer->isActive())
        painter->drawText(boundingRect(), Qt::AlignCenter, "PAUSE");
    else
        painter->drawText(boundingRect(), Qt::AlignCenter, "CONTINUE");
}

void GameWidget::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (timer->isActive())
        {
//            sound->stop();
            timer->stop();
            board=new ScoreBoard;
            board->setPos(390,100);
            scene()->addItem(board);
        }
        else
        {
            delete board;
//            sound->play();
            timer->start();
        }
    }
    update();
}

ScoreBoard::ScoreBoard():Pixmap(":/new/src/Screen/pause_window.png"){}

void ScoreBoard::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawPixmap(0,0,pixmap);
    painter->setPen(Qt::green);
    QFont font("Calibri", 24, QFont::Bold, true);
    painter->setFont(font);
    QString str="Score:"+QString::number(gamewindow::sumScore);
    painter->drawText(boundingRect(), Qt::AlignCenter, str);
}
