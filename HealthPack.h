#ifndef HEALTHPACK_H
#define HEALTHPACK_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <QMediaPlayer>

#include "world.h"


class HealthPack:public Tile, public QGraphicsPixmapItem{
public:
    HealthPack(int xPosition, int yPosition, float tileWeight);
private:

};


#endif // HEALTHPACK_H
