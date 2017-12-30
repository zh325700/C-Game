#ifndef MYMODEL_H
#define MYMODEL_H

#include<QWidget>
#include <math.h>
#include <limits.h>

#include "MyProtagonist.h"
#include "MyEnemy.h"
#include "MyTile.h"
#include "MyPEnemy.h"
#include "HealthPack.h"
#include "world.h"
#include "GraphicGameView.h"
#include "Astar.h"



class MyModel{
public:
    MyModel(QString map);
    ~MyModel();

    void modelInitialize();

    /*moving and strategy*/
    bool moveFast();      //move to a certain position
    bool FindNextStep();
    void gotoNextEnemy();
    void gotoNextPEnemy();
    MyEnemy ** findNearestEnemy();
    MyPEnemy ** findNearestPEnemy();
    HealthPack ** findNearestHealthPack();
    int calculateDistance(int givenX, int givenY);    //simplified but faster version, can be improved later if needed

    /*saving and loading*/
    void saveGame(QString filename);
    void loadGame(QString filename);
    void clearAllSaves();

    /*getters and setters*/
    bool getWhichView() const;
    void setWhichView(bool value);
    int & getCols() ;
    void setCols(int value);
    int & getRows() ;
    void setRows(int value);
    MyProtagonist *getMyProtagonist() ;
    void setMyProtagonist(MyProtagonist *value);
    std::vector<MyTile *> & getMyTilesMap() ;
    void setMyTilesMap( std::vector<MyTile *> &value);
    std::vector<MyEnemy *> & getMyEnemies() ;
    void setMyEnemies( std::vector<MyEnemy *> &value);
    std::vector<MyPEnemy *> & getMyPEnemies() ;
    void setMyPEnemies( std::vector<MyPEnemy *> &value);
    std::vector<HealthPack *> & getMyHealthPacks() ;
    void setMyHealthPacks( std::vector<HealthPack *> &value);
    int getDestinationX() const;
    void setDestinationX(int value);
    int getDestinationY() const;
    void setDestinationY(int value);
    std::shared_ptr<Astar> getMyAstar() const;
    bool getReadyToNext() const;
    void setReadyToNext(bool value);
    float getW() const;
    void setW(float value);
    int getNrOfEnemies() const;
    void setNrOfEnemies(int value);
    int getNrOfHealthPacks() const;
    void setNrOfHealthPacks(int value);
    bool getOnceOrMore() const;
    void setOnceOrMore(bool value);
    int getSpeed() const;
    void setSpeed(int value);

private:
    int cols;
    int rows;
    int destinationX;
    int destinationY;
    int speed = 200;
    float w = 1.0;
    bool readyToNext;
    bool whichView = false;
    int nrOfEnemies = 50;
    int nrOfHealthPacks = 500;
    bool onceOrMore = true;
    MyEnemy ** nearestEnemy = nullptr;
    MyPEnemy ** nearestPEnemy = nullptr;
    HealthPack ** nearestHP = nullptr;
    MyProtagonist *myProtagonist;
    std::shared_ptr<World> world;

    std::vector<MyTile *> myTilesMap ={};
    std::vector<MyEnemy *> myEnemies ={};
    std::vector<MyPEnemy *> myPEnemies ={};
    std::vector<HealthPack *> myHealthPacks ={};

    std::shared_ptr<Astar> myAstar;
    std::vector<std::unique_ptr<Tile>> mapTiles;

};

#endif // MYMODEL_H
