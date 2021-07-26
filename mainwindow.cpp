#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPalette>
#include <QBrush>
#include <QIcon>
#include "include/common.h"
#include "game/gamewindow.h"
#include<QLabel>
#include<QMovie>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //mainwindow config
    this->setFixedSize(WINDOWSWIDTH,WINDOWSHEIGHT);
    this->setWindowTitle("Plants vs Zombies (GUI) | By Shen Tianjie");
    this->setWindowIcon(QIcon(":/new/src/Icon/pvz_icon.png"));

    //welcome menu config
    QPalette pale;
    pale.setBrush(QPalette::Background,QBrush(QPixmap(":/new/src/Screen/MainMenu.png")));
    this->setPalette(pale);

    //pushbutton config
    this->startbtn=new QPushButton(this);
    this->startbtn->setIcon(QIcon(":/new/src/Screen/Adventure_0.png"));
    this->startbtn->setIconSize(QSize(STARTBTNWIDTH,STARTBTNHEIGHT));
    this->startbtn->setFocusPolicy(Qt::NoFocus);
    this->startbtn->setFlat(true);
    this->startbtn->setGeometry(startbtn_offset[0],startbtn_offset[1], STARTBTNWIDTH,STARTBTNHEIGHT);

    //sub game window init

    this->connect(startbtn,SIGNAL(clicked(bool)),this,SLOT(startbtnclick()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startbtnclick()
{
    gw.show();
    this->hide();
}
