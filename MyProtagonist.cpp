#include "MyProtagonist.h"
#include "Game.h"
#include <QKeyEvent>
#include <QGraphicsScene>
#include <math.h>


extern Game *game;
MyProtagonist::MyProtagonist(QGraphicsItem *parent):
    QGraphicsPixmapItem(parent),Protagonist()
{
    //set the origin position of protahonist
    this->QGraphicsItem::setPos(xPos*sizeOfTile,yPos*sizeOfTile);
    setPixmap(QPixmap(":/images/icons/Protagonist.png"));
    //set initial value to tile value, size of tile and stepCost for each step
    sizeOfTile = 20;
    stepCost =1.0;
//    this->setValue(getTileByXY(this->getXPos()/sizeOfTile,this->getYPos()/sizeOfTile,game->myTilesMap,game->cols)->getValue());
}

void MyProtagonist::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left){
        if (xPos > 0 && !isinf(getNextSpotValue(xPos/sizeOfTile-1,yPos/sizeOfTile,game->myTilesMap,game->cols)))
        {
            Protagonist::setPos(xPos-sizeOfTile,yPos);
            Protagonist::setEnergy(Protagonist::getEnergy()-stepCost);
        }
    }
    else if (event->key() == Qt::Key_Right){
        if(!isinf(getNextSpotValue(xPos/sizeOfTile+1,yPos/sizeOfTile,game->myTilesMap,game->cols))
                &&xPos<game->cols*sizeOfTile){   // 800 and 20 should be changeble with the size of the tile
            Protagonist::setPos(xPos+sizeOfTile,yPos);
            Protagonist::setEnergy(Protagonist::getEnergy()-stepCost);
        }
    }
    else if(event->key()== Qt::Key_Up){
        if(yPos >0 && !isinf(getNextSpotValue(xPos/sizeOfTile,yPos/sizeOfTile-1,game->myTilesMap,game->cols))){
            Protagonist::setPos(xPos,yPos-sizeOfTile);
            Protagonist::setEnergy(Protagonist::getEnergy()-stepCost);
        }
    }
    else if(event->key() == Qt::Key_Down){
        if(!isinf(getNextSpotValue(xPos/sizeOfTile,yPos/sizeOfTile+1,game->myTilesMap,game->cols))
                &&yPos<game->rows*sizeOfTile){
            Protagonist::setPos(xPos,yPos+sizeOfTile);
            Protagonist::setEnergy(Protagonist::getEnergy()-stepCost);
        }
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
    game->centerOn(this);
}

void MyProtagonist::decreaseHealth(float healthCost)
{
    setHealth(getHealth()-healthCost);
}

void MyProtagonist::recoverHealth()
{
    setHealth(100.0);
}

MyTile *MyProtagonist::getTileByXY(int x, int y, std::vector<MyTile *> &myTiles, int &world_cols)
{
    int index = x + y*world_cols;
    return myTiles[index];
}

void MyProtagonist::aquire_target(){      //  collide Tile or protagonist
    // get a list of all items colliding with attack_area
    QList<QGraphicsItem *> colliding_items = this->collidingItems();

    if (colliding_items.size() == 1){
        MyTile *aMyTile = dynamic_cast<MyTile *>(colliding_items[0]); // already next Tile
        float costOfStep =this->getValue()-aMyTile->getValue();   //previous value - Next Tile value
        this->setValue(aMyTile->getValue());    //set value to thisi Tile
        this->setEnergy(this->getEnergy()-abs(costOfStep));    // - costOfStep which is the difference between twoo tiles
        return;
    }
    else{
            for (size_t i = 0, n = colliding_items.size(); i < n; i++){
                MyEnemy * aMyenemy = dynamic_cast<MyEnemy *>(colliding_items[i]);
                MyPEnemy *aPenemy = dynamic_cast<MyPEnemy *>(colliding_items[i]);
                HealthPack *aHealthPack = dynamic_cast<HealthPack *>(colliding_items[i]);

                if (aMyenemy){
                    decreaseHealth(aMyenemy->getValue());
//                    this->setHealth(this->getHealth()-aMyenemy->getValue());     // If encounter with enemy,kill, decrease health,set black
                    this->getTileByXY(this->getXPos()/sizeOfTile,this->getYPos()/sizeOfTile,game->myTilesMap,game->cols)->setValue(std::numeric_limits<float>::infinity());
                    aMyenemy->setDefeated(true);
                    delete aMyenemy;
                }
                else if(aPenemy){
                    delete aPenemy;
                }
                else if(aHealthPack){
                    recoverHealth();
//                    this->setHealth(100.0);
                    delete aHealthPack;
                }
            }
        }


}
