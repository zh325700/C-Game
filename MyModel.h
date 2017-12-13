#ifndef MYMODEL_H
#define MYMODEL_H

#include "MyProtagonist.h"
#include "MyEnemy.h"
#include "MyTile.h"
#include "MyPEnemy.h"
#include "HealthPack.h"
#include "world.h"
#include "Game.h"


class MyModel
{
public:
    MyModel();
    ~MyModel();

    int cols;
    int rows;
    MyProtagonist *myProtagonist;
    std::vector<MyTile *> myTilesMap ={};
    std::vector<MyEnemy *> myEnemies ={};
    std::vector<MyPEnemy *> myPEnemies ={};
    std::vector<HealthPack *> myHealthPacks ={};

};

#endif // MYMODEL_H
