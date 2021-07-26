#ifndef SHOP_H
#define SHOP_H
#include"include/pixmap.h"

class Shop:public Pixmap
{
public:
    Shop();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void addSun(int val);
    int getSun(){return total_sun;}
    void addPlant(QString name,QPointF p);
    void refreshPlant(QPointF p);
    void refreshPumpkin(QPointF p);
    bool hasOccupied(int i,int j){
        if(i<0||i>=5||j<0||j>=9)
            return false;
        return is_occupied[i][j];
    }
    bool hasDefender(int i,int j){
        if(i<0||i>=5||j<0||j>=9)
            return false;
        return active_defender[i][j];
    }
    void clearOccupied(int i,int j){is_occupied[i][j]=false;}
    void clearDefender(int i,int j){active_defender[i][j]=false;}
private:
    int total_sun,counter;
    bool is_occupied[5][9];
    bool active_defender[5][9];
};

#endif // SHOP_H
