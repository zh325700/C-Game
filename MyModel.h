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


class MyModel
{
public:
    MyModel();
    ~MyModel();
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

private:
    int cols;
    int rows;
    int destinationX;
    int destinationY;
    MyProtagonist *myProtagonist;
    std::vector<MyTile *> myTilesMap ={};
    std::vector<MyEnemy *> myEnemies ={};
    std::vector<MyPEnemy *> myPEnemies ={};
    std::vector<HealthPack *> myHealthPacks ={};
    bool whichView = false;

};

#endif // MYMODEL_H
