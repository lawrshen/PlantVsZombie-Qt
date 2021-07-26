#include "shop.h"
#include<QFont>
#include<QRectF>
#include<QString>
#include"card.h"
#include"src/plants/plant.h"
#include"include/common.h"

Shop::Shop():Pixmap(":/new/src/Screen/Shop.png")
{
    total_sun = 500;
    counter=0;
    for(int i=0;i<5;i++){
        for(int j=0;j<9;j++){
            is_occupied[i][j]=false;
            active_defender[i][j]=false;
        }
    }
    Card* cards=nullptr;
    for (int i = 0; i < Card::name.size(); ++i)
    {
        cards = new Card(Card::name[i]);
        cards->setParentItem(this);
        cards->setPos(70+62*i,0);
    }
}

void Shop::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawPixmap(0,0,pixmap);
    QFont font;
    font.setPointSizeF(13);
    painter->setFont(font);
    painter->drawText(QRectF(0,0,pixmap.width()-370,pixmap.height()+60), Qt::AlignCenter, QString::number(total_sun));
}

void Shop::addSun(int val)
{
    total_sun += val;
    update();
}

void Shop::addPlant(QString name,QPointF p)
{
    int j=(p.x()-plt_base.x())/obj_offset.x(),i=(p.y()-plt_base.y())/obj_offset.y();
    if(i<0||i>=5||j<0||j>=9||is_occupied[i][j]){
        if(active_defender[i][j] || name != "Pumpkin")
            return;
        else
            active_defender[i][j]=true;
    }
    else{
        if(name == "Pumpkin")
            return;
        is_occupied[i][j]=true;
    }
    addSun(-Card::cost[Card::map[name]]);
    Plant *plant = nullptr;
    switch (Card::map[name])
    {
        case 0:
            plant = new SunFlower; break;
        case 1:
            plant = new Peashooter; break;
        case 2:
            plant = new SnowPea; break;
        case 3:
            plant = new Repeater; break;
        case 4:
            plant = new WallNut; break;
        case 5:
            plant = new TallNut; break;
        case 6:
            plant = new Cherrybomb; break;
        case 7:
            plant = new Squash; break;
        case 8:
            plant = new Garlic; break;
        case 9:
            plant = new Pumpkin; break;
      default:
        return;
    }
    plant->setPos(p);
    scene()->addItem(plant);
    QList<QGraphicsItem *> child = childItems();
    foreach (QGraphicsItem *item, child)
    {
        Card *card = qgraphicsitem_cast<Card *>(item);
        if (card->getName() == name)
            card->resetCounter();
    }
    counter = 0;
}

void Shop::refreshPlant(QPointF p)
{
    int j=(p.x()-plt_base.x())/obj_offset.x(),i=(p.y()-plt_base.y())/obj_offset.y();
    is_occupied[i][j]=false;
}

void Shop::refreshPumpkin(QPointF p)
{
    int j=(p.x()-plt_base.x())/obj_offset.x(),i=(p.y()-plt_base.y())/obj_offset.y();
    active_defender[i][j]=false;
}
