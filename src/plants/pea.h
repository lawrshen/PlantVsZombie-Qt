#ifndef PEA_H
#define PEA_H
#include"include/pixmap.h"

class Pea: public Pixmap
{
public:
    Pea(int _demage,bool _snow=false);
    void paint();
    void advance(int phase);
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const;

private:
    int demage;
    bool snow;
};

#endif // PEA_H
