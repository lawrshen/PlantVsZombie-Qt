#ifndef COMMON_H
#define COMMON_H
#include<QPoint>

#define WINDOWSWIDTH 900
#define WINDOWSHEIGHT 600
#define STARTBTNWIDTH 200
#define STARTBTNHEIGHT 100
const static int startbtn_offset[2]={530,120};
const static int game_windows[2]={1100,600};
const static QPoint plt_base=QPoint(250,100);
const static QPoint zom_base=QPoint(1000,50);
const static QPoint obj_offset=QPoint(81,92);
enum ZombieCard { NormalZombieCard, ConeheadZombieCard, NewspaperZombieCard, PoleVaultingZombieCard, JokerZombieCard, CatapultZombieCard,NoneZomCard};


#endif // COMMON_H
