#ifndef MYPROTAGONIST_H
#define MYPROTAGONIST_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsItem>
#include <QMediaPlayer>
#include <vector>
#include <QTimer>

#include "world.h"
#include "MyTile.h"

class MyProtagonist:public Protagonist, public QGraphicsPixmapItem{
    Q_OBJECT  // if you want to have signal and slot you have to be a QObject
public:
    QTimer * timer;
    unsigned countSteps = 0;

    MyProtagonist(QGraphicsItem * parent=0);  // allow you yo have a parent point

    void keyPressEvent(QKeyEvent * event);

    /*to get tiles and tile values from tile vector*/
    float getNextSpotValue(int x,int y, std::vector<MyTile *> &myTiles,int &world_cols);
    MyTile *getTileByXY(int x,int y, std::vector<MyTile *> &myTiles,int &world_cols);

    /*to change health and energy*/
    float decreaseHealth(float healthCost);
    void recoverHealth(float health);
    void recoverEnergy();

    /*getters and setters*/
    float getStepCost() const;
    void setStepCost(float value);
    int getSizeOfTile() const;
    void setSizeOfTile(int value);
    bool getPaused() const;
    void setPaused(bool value);
    bool getAlReadyDrawCircle() const;
    void setAlReadyDrawCircle(bool value);
    unsigned getCountSteps() const;
    void setCountSteps(const unsigned &value);


signals:
    void protagonistDead();
    void encounterPenemy();
    void encounterEnemy();
    void encounterHealthPack();
    void inCircle();
    void findNext();

public slots:
    void moveToNextSpot();
    void aquire_target();
    void checkProtagonistDead();
    void ifInPoisonarea(float poisonValue);
    void moveAlongWithPath();
private :
    int sizeOfTile;
    float stepCost;
    int graphicX=0;
    int graphicY=0;
    bool paused = false;
    bool alReadyDrawCircle = false;



};


#endif // MYPROTAGONIST_H
