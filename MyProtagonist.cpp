#include <QKeyEvent>
#include <QGraphicsScene>
#include <math.h>
#include <QMessageBox>
#include <QDebug>

#include "MyProtagonist.h"
#include "Game.h"


extern Game *game;
MyProtagonist::MyProtagonist(QGraphicsItem *parent):
    QGraphicsPixmapItem(parent),Protagonist()
{
    //set the origin position of protahonist
    this->QGraphicsItem::setPos(xPos*sizeOfTile,yPos*sizeOfTile);
    setPixmap(QPixmap(":/images/icons/protagonistNew.png"));
    //set initial value to tile value, size of tile and stepCost for each step
    setSizeOfTile(20);
    setStepCost(0.0);
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
    else if(event->key() == Qt::Key_Space){
        this->setFocus();
        game->centerOn(this);
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

void MyProtagonist::recoverEnergy()
{
    setEnergy(100.0);
}

MyTile *MyProtagonist::getTileByXY(int x, int y, std::vector<MyTile *> &myTiles, int &world_cols)
{
    int index = x + y*world_cols;
    return myTiles[index];
}

void MyProtagonist::aquire_target(){      //  collide Tile or protagonist
    // get a list of all items colliding with attack_area
    QList<QGraphicsItem *> colliding_items = this->collidingItems();

            for (size_t i = 0, n = colliding_items.size(); i < n; i++){
                MyEnemy * aMyenemy = dynamic_cast<MyEnemy *>(colliding_items[i]);
                MyPEnemy *aPenemy = dynamic_cast<MyPEnemy *>(colliding_items[i]);
                HealthPack *aHealthPack = dynamic_cast<HealthPack *>(colliding_items[i]);
                MyTile *aMyTile = dynamic_cast<MyTile *>(colliding_items[i]);
                if (aMyenemy){
                     qDebug() << "Enemy strength: " <<aMyenemy->getValue();
                     // If encounter with enemy,kill, decrease health,set black
                    decreaseHealth(aMyenemy->getValue());
                    recoverEnergy();
                    this->getTileByXY(this->getXPos()/sizeOfTile,this->getYPos()/sizeOfTile,game->myTilesMap,game->cols)->setValue(std::numeric_limits<float>::infinity());
                    aMyenemy->setDefeated(true);   //set defeated then emit dead()
                    game->scene->removeItem(aMyenemy);
                    delete aMyenemy;
                }
                else if(aPenemy){
                    qDebug() << "PEnemy strength: " <<aPenemy->getValue();
                    decreaseHealth(aPenemy->getValue());
                    recoverEnergy();
                    this->getTileByXY(this->getXPos()/sizeOfTile,this->getYPos()/sizeOfTile,game->myTilesMap,game->cols)->setValue(std::numeric_limits<float>::infinity());
                    emit encounterPenemy();  // emit signal encounterpenemy, So enemy can start poinsoning
                }
                else if(aHealthPack){
                    recoverHealth();
                    game->scene->removeItem(aHealthPack);
                    delete aHealthPack;
                }
                else if(aMyTile){
                    float costOfStep =this->getValue()-aMyTile->getValue();   //previous value - Next Tile value
                    if(abs(costOfStep) == std::numeric_limits<float>::infinity()){
                        costOfStep=0;
                    }
                    this->setValue(aMyTile->getValue());    //set value to this Tile
                    qDebug()<<"The cost is"<<abs(costOfStep);
                    this->setEnergy(this->getEnergy()-abs(costOfStep));    // - costOfStep which is the difference between twoo tiles
                }
            }



}
void MyProtagonist::checkProtagonistDead()
{
    if(getHealth()<=0 || getEnergy()<=0){
        setPixmap(QPixmap(":/images/icons/deadEnemy.png"));
        emit protagonistDead();
    }
}

void MyProtagonist::ifInPoisonarea(float poisonValue)
{
    QList<QGraphicsItem *> colliding_items = this->collidingItems();
    for (size_t i = 0, n = colliding_items.size(); i < n; i++){
//        qDebug()<<"collid item: "<<typeid(*colliding_items[i]);
        QGraphicsEllipseItem * aCircle = dynamic_cast<QGraphicsEllipseItem *>(colliding_items[i]);
        if(aCircle){
                this->setHealth(this->getHealth()-poisonValue/1000);
        }
    }
}

void MyProtagonist::setSizeOfTile(int value)
{
    sizeOfTile = value;
}

float MyProtagonist::getStepCost() const
{
    return stepCost;
}

void MyProtagonist::setStepCost(float value)
{
    stepCost = value;
}

int MyProtagonist::getSizeOfTile() const
{
    return sizeOfTile;
}



