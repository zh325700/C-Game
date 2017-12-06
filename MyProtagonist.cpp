#include "MyProtagonist.h"
#include "Game.h"
#include <QKeyEvent>
#include <QGraphicsScene>
#include <math.h>


extern Game *game;
MyProtagonist::MyProtagonist(QGraphicsItem *parent):
    QGraphicsPixmapItem(parent),Protagonist()
{
    setPixmap(QPixmap(":/images/Protagonist.png"));
}

void MyProtagonist::keyPressEvent(QKeyEvent *event)
{
    int sizeOfTile = 20;
    if (event->key() == Qt::Key_Left){
        if (pos().x() > 0 && !isinf(getNextSpotValue(xPos/sizeOfTile-1,yPos/sizeOfTile,game->myTilesMap,game->cols)))
        Protagonist::setPos(xPos-sizeOfTile,yPos);
    }
    else if (event->key() == Qt::Key_Right &&!isinf(getNextSpotValue(xPos/sizeOfTile+1,yPos/sizeOfTile,game->myTilesMap,game->cols))){   // 800 and 20 should be changeble with the size of the tile
//        if (pos().x() + 20 < 800)
        Protagonist::setPos(xPos+sizeOfTile,yPos);
    }
    else if(event->key()== Qt::Key_Up && !isinf(getNextSpotValue(xPos/sizeOfTile,yPos/sizeOfTile-1,game->myTilesMap,game->cols))){
        Protagonist::setPos(xPos,yPos-sizeOfTile);
    }
    else if(event->key() == Qt::Key_Down &&! isinf(getNextSpotValue(xPos/sizeOfTile,yPos/sizeOfTile+1,game->myTilesMap,game->cols))){
        Protagonist::setPos(xPos,yPos+sizeOfTile);
    }
}

float MyProtagonist::getNextSpotValue(int x, int y, std::vector<MyTile *> &myTiles, int &world_cols)
{
    int index = x + y*world_cols;
    return myTiles[index]->getValue();
}

void MyProtagonist::moveToNextSpot()
{
    QGraphicsItem::setPos(xPos,yPos);
}
