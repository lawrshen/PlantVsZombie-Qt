#ifndef PIXMAP_H
#define PIXMAP_H
#include<QGraphicsView>
#include<QGraphicsItem>
#include<QPainter>
#include<QPixmap>
#include<QString>
class Pixmap:public QGraphicsItem
{
public:
    Pixmap(const QString& filename);
    QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
protected:
    QPixmap pixmap;
};

#endif // PIXMAP_H
