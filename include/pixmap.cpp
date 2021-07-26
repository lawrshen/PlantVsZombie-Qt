#include "pixmap.h"

Pixmap::Pixmap(const QString& filename)
{
    pixmap.load(filename);
}

QRectF Pixmap::boundingRect() const
{
    return QRectF(0,0,pixmap.width(),pixmap.height());
}

void Pixmap::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(0,0,pixmap);
}
