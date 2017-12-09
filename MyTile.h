#ifndef MYTILE_H
#define MYTILE_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <QMediaPlayer>
#include <QPaintEvent>

#include "world.h"

class MyTile:public QObject,public Tile, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    MyTile(int xPosition, int yPosition, float tileWeight);
public slots:
    void drawBlack();
private :
};



#endif // MYTILE_H
