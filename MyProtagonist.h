#ifndef MYPROTAGONIST_H
#define MYPROTAGONIST_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsItem>
#include <QMediaPlayer>
#include <vector>

#include "world.h"
#include "MyTile.h"

class MyProtagonist:public Protagonist, public QGraphicsPixmapItem{
    Q_OBJECT  // if you want to have signal and slot you have to be a QObject
public:
    MyProtagonist(QGraphicsItem * parent=0);  // allow you yo have a parent point
    void keyPressEvent(QKeyEvent * event);
    float getNextSpotValue(int x,int y, std::vector<MyTile *> &myTiles,int &world_cols);
    void decreaseHealth(float healthCost);
    void recoverHealth();
    void recoverEnergy();
    MyTile *getTileByXY(int x,int y, std::vector<MyTile *> &myTiles,int &world_cols);


    float getStepCost() const;
    void setStepCost(float value);
    int getSizeOfTile() const;
    void setSizeOfTile(int value);

signals:
    void protagonistDead();
    void encounterPenemy();
public slots:
    void moveToNextSpot();
    void aquire_target();
    void checkProtagonistDead();
    void ifInPoisonarea(float poisonValue);
private :
    int sizeOfTile;
    float stepCost;

};


#endif // MYPROTAGONIST_H