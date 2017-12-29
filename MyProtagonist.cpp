#include <QKeyEvent>
#include <QGraphicsScene>
#include <math.h>
#include <QMessageBox>
#include <QDebug>


#include "MyProtagonist.h"
#include "GraphicGameView.h"
#include "MyModel.h"


extern GraphicGameView *graphicGameView;
extern MyModel *myModel;

MyProtagonist::MyProtagonist(QGraphicsItem *parent):
    Protagonist(),QGraphicsPixmapItem(parent)
{
    this->Protagonist::setPos(7,7);
    setSizeOfTile(20);
    setStepCost(0.05);
    //set the origin position of protahonist
    this->setXPos(7);
    this->setYPos(7);
    this->graphicX = xPos*getSizeOfTile();
    this->graphicY = yPos*getSizeOfTile();

    this->QGraphicsItem::setPos(graphicX,graphicY);
    setPixmap(QPixmap(":/images/icons/protagonistNew.png"));
    //set initial value to tile value, size of tile and stepCost for each step
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(moveAlongWithPath()));

}

void MyProtagonist::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left){
        if (xPos > 0 && !isinf(getNextSpotValue(xPos-1,yPos,myModel->getMyTilesMap(),myModel->getCols())))
        {
            Protagonist::setPos(xPos-1,yPos);
        }
    }
    else if (event->key() == Qt::Key_Right){
        if(!isinf(getNextSpotValue(xPos+1,yPos,myModel->getMyTilesMap(),myModel->getCols()))
                &&xPos<myModel->getCols()){   // 800 and 20 should be changeble with the size of the tile
            Protagonist::setPos(xPos+1,yPos);
        }
    }
    else if(event->key()== Qt::Key_Up){
        if(yPos >0 && !isinf(getNextSpotValue(xPos,yPos-1,myModel->getMyTilesMap(),myModel->getCols()))){
            Protagonist::setPos(xPos,yPos-1);
        }
    }
    else if(event->key() == Qt::Key_Down){
        if(!isinf(getNextSpotValue(xPos,yPos+1,myModel->getMyTilesMap(),myModel->getCols()))
                &&yPos<myModel->getRows()){
            Protagonist::setPos(xPos,yPos+1);
        }
    }
    else if(event->key() == Qt::Key_Space){
        this->setFocus();
        graphicGameView->centerOn(this);
    }
}

float MyProtagonist::getNextSpotValue(int x, int y, std::vector<MyTile *> &myTiles, int &world_cols)
{
    int index = x + y*world_cols;
    return myTiles[index]->getValue();
}

void MyProtagonist::moveToNextSpot()
{
    graphicX = xPos*getSizeOfTile();
    graphicY = yPos*getSizeOfTile();
    QGraphicsItem::setPos(graphicX,graphicY);
    graphicGameView->centerOn(this);
}

float MyProtagonist::decreaseHealth(float healthCost)
{
    float currentHealth = getHealth()-healthCost;
    setHealth(currentHealth);
    return currentHealth;
}

void MyProtagonist::recoverHealth(float health)
{
    if((getHealth()+health)>=100){
        setHealth(100.0f);
    }else{
        setHealth(getHealth()+health);
    }

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
    Protagonist::setEnergy(Protagonist::getEnergy()-stepCost);

    QList<QGraphicsItem *> colliding_items = this->collidingItems();

            for (size_t i = 0, n = colliding_items.size(); i < n; i++){
                MyEnemy * aMyenemy = dynamic_cast<MyEnemy *>(colliding_items[i]);
                MyPEnemy *aPenemy = dynamic_cast<MyPEnemy *>(colliding_items[i]);
                HealthPack *aHealthPack = dynamic_cast<HealthPack *>(colliding_items[i]);
                MyTile *aMyTile = dynamic_cast<MyTile *>(colliding_items[i]);
                if (aMyenemy){
                     // If encounter with enemy,kill, decrease health,set black
                    emit encounterEnemy();
                    float currentHealth = decreaseHealth(aMyenemy->getValue());
                    if(currentHealth<=0) return;
                    recoverEnergy();
                    this->getTileByXY(this->getXPos(),this->getYPos(),myModel->getMyTilesMap(),myModel->getCols())->setValue(std::numeric_limits<float>::infinity());
                    aMyenemy->setDefeated(true);   //set defeated then emit dead()

                }
                else if(aPenemy){
                    qDebug() << "PEnemy strength: " <<aPenemy->getValue();
                    float currentHealth = decreaseHealth(aPenemy->getValue()/10);
                    if(currentHealth<=0) return;
                    recoverEnergy();
                    this->getTileByXY(this->getXPos(),this->getYPos(),myModel->getMyTilesMap(),myModel->getCols())->setValue(std::numeric_limits<float>::infinity());
                    QObject::connect(this,&MyProtagonist::encounterPenemy,aPenemy,&MyPEnemy::poison);
                    emit encounterPenemy();  // emit signal encounterpenemy, So enemy can start poinsoning
                    qDebug()<<"The poison level is"<<aPenemy->getPoisonLevel();
                }
                else if(aHealthPack){
                    emit encounterHealthPack();
                    recoverHealth(aHealthPack->getValue());
                    graphicGameView->scene->removeItem(aHealthPack);
                    delete aHealthPack;
                    for(unsigned i=0;i<myModel->getMyHealthPacks().size();i++){
                        if(myModel->getMyHealthPacks()[i] == aHealthPack){
                            myModel->getMyHealthPacks().erase(myModel->getMyHealthPacks().begin()+i);
                        }
                    }
                }
                else if(aMyTile){
                    float costOfStep =this->getValue()-aMyTile->getValue();   //previous value - Next Tile value
                    if(abs(costOfStep) == std::numeric_limits<float>::infinity()){
                        costOfStep=0;
                    }
                    this->setValue(aMyTile->getValue());    //set value to this Tile
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
        QGraphicsEllipseItem * aCircle = dynamic_cast<QGraphicsEllipseItem *>(colliding_items[i]);
        if(aCircle){
                this->setHealth(this->getHealth()-poisonValue/10);
                emit inCircle();
        }
    }
}

void MyProtagonist::moveAlongWithPath()
{
    if(!getPaused()){
        int totalSize = myModel->getMyAstar()->getSolution().size();
        if(countSteps<myModel->getMyAstar()->getSolution().size())
        {
            int x = myModel->getMyAstar()->getSolution()[totalSize - countSteps - 1]->getPos_x();

            int y = myModel->getMyAstar()->getSolution()[totalSize - countSteps - 1]->getPos_y(); //move along the path

            graphicGameView->scene->removeItem(graphicGameView->getPathTiles()[countSteps]); //remove the path
            this->Protagonist::setPos(x,y);

            countSteps ++;
        }else{
            timer->stop();
            countSteps = 0;
            graphicGameView->pathTiles.clear();
            if (! myModel->getOnceOrMore()) emit findNext();
        }
    }

}

bool MyProtagonist::getAlReadyDrawCircle() const
{
    return alReadyDrawCircle;
}

void MyProtagonist::setAlReadyDrawCircle(bool value)
{
    alReadyDrawCircle = value;
}

bool MyProtagonist::getPaused() const
{
    return paused;
}

void MyProtagonist::setPaused(bool value)
{
    paused = value;
}

void MyProtagonist::setSizeOfTile(int value)
{
    sizeOfTile = value;
}

unsigned MyProtagonist::getCountSteps() const
{
    return countSteps;
}

void MyProtagonist::setCountSteps(const unsigned &value)
{
    countSteps = value;
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



