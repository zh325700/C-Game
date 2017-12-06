#ifndef MYTILE_H
#define MYTILE_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <QMediaPlayer>
#include <QPaintEvent>
#include "world.h"

class MyTile:public Tile, public QGraphicsRectItem{
public:
    MyTile(int xPosition, int yPosition, float tileWeight);
private :
};



#endif // MYTILE_H
