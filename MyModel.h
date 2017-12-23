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

private:
    int cols;
    int rows;
    MyProtagonist *myProtagonist;
    std::vector<MyTile *> myTilesMap ={};
    std::vector<MyEnemy *> myEnemies ={};
    std::vector<MyPEnemy *> myPEnemies ={};
    std::vector<HealthPack *> myHealthPacks ={};
<<<<<<< HEAD
    bool getWhichView() const;
    void setWhichView(bool value);

    std::vector<MyEnemy *> getMyEnemies() const;
    void setMyEnemies(const std::vector<MyEnemy *> &value);

private:
=======
>>>>>>> 10a33936e485defa3edd97031f6021e5920cd212
    bool whichView = false;

};

#endif // MYMODEL_H
