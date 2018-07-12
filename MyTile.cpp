#include "MyTile.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QBrush>
#include <QRect>


MyTile::MyTile(int xPosition, int yPosition, float tileWeight):
    Tile(xPosition, yPosition, tileWeight)
{

    this->setPos(xPos*20,yPos*20);
    if(value<0.8){
        setPixmap(QPixmap(":/images/icons/blueSea.jpg"));
    }
    else if(value<=1 && value>0.8){
        setPixmap(QPixmap(":/images/icons/white.jpg"));
    }
    else {
        setPixmap(QPixmap(":/images/icons/rock.png"));
    }

}

void MyTile::drawBlack()
{
    setPixmap(QPixmap(":/images/icons/deadEnemy.png"));
}



