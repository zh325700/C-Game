#ifndef MYTILE_H
#define MYTILE_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <QMediaPlayer>
#include <QPaintEvent>

#include "world.h"

class MyTile:public QObject,public Tile, public QGraphicsRectItem{
    Q_OBJECT
public:
    MyTile(int xPosition, int yPosition, float tileWeight);
public slots:
    void drawBlack();
    void drawPoision();
private :
};



#endif // MYTILE_H
