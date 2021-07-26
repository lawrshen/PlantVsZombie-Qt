#-------------------------------------------------
#
# Project created by QtCreator 2021-05-13T09:12:37
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qt_pvz
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    game/gamewindow.cpp \
    src/liveobject.cpp \
    src/zombie.cpp \
    src/plants/plant.cpp \
    src/plants/sun.cpp \
    src/plants/pea.cpp \
    game/shop.cpp \
    include/pixmap.cpp \
    game/card.cpp \
    game/garden.cpp \
    game/gamewidget.cpp

HEADERS  += mainwindow.h \
    include/common.h \
    game/gamewindow.h \
    src/liveobject.h \
    src/zombie.h \
    src/plants/plant.h \
    src/plants/sun.h \
    src/plants/pea.h \
    game/shop.h \
    include/pixmap.h \
    game/card.h \
    game/garden.h \
    game/gamewidget.h

FORMS    += mainwindow.ui

RESOURCES += \
    graphics/graphics.qrc


