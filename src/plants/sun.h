#ifndef SUN_H
#define SUN_H
#include<QGraphicsItem>
#include<QPainter>
#include<QMovie>
#include<QMouseEvent>
class Sun: public QGraphicsItem
{
public:
    Sun(bool _env=false);
    ~Sun();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phase);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    QMovie* movie;
    int counter;
    int active_clk;
    bool is_env;
};

#endif // SUN_H
