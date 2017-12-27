#ifndef MYMODEL_H
#define MYMODEL_H
#include<QWidget>

#include "MyProtagonist.h"
#include "MyEnemy.h"
#include "MyTile.h"
#include "MyPEnemy.h"
#include "HealthPack.h"
#include "world.h"
#include "GraphicGameView.h"
#include "Astar.h"
#include <math.h>
#include <limits.h>


class MyModel
{
public:
    MyModel(QString map = ":/images/maps/worldmap.png",int enemyNum = 50,int healthpackNum = 500);
    ~MyModel();

    bool moveFast();      //move to a certain position
    void FindNextStep();
    MyEnemy ** findNearestEnemy();
    MyPEnemy ** findNearestPEnemy();
    HealthPack ** findNearestHealthPack();
    int calculateDistance(int givenX, int givenY);    //simplified but faster version, can be improved later if needed

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

private:
    int cols;
    int rows;
    int destinationX;
    int destinationY;
    bool readyToNext;
    MyProtagonist *myProtagonist;
    std::vector<MyTile *> myTilesMap ={};
    std::vector<MyEnemy *> myEnemies ={};
    std::vector<MyPEnemy *> myPEnemies ={};
    std::vector<HealthPack *> myHealthPacks ={};
    bool whichView = false;
    std::shared_ptr<Astar> myAstar;
    std::vector<std::unique_ptr<Tile>> mapTiles;

};

#endif // MYMODEL_H
