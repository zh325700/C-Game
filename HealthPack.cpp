#include <QGraphicsScene>
#include <QDebug>

#include "HealthPack.h"



HealthPack::HealthPack(int xPosition, int yPosition, float tileWeight):
    Tile(xPosition, yPosition, tileWeight)
{
    int sizeOfTile = 20;
    this->setPos(xPosition*sizeOfTile,yPosition*sizeOfTile);
    setPixmap(QPixmap(":/images/icons/healthpack.png"));
}
