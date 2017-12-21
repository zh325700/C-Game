#ifndef MYMODEL_H
#define MYMODEL_H
#include<QWidget>

#include "MyProtagonist.h"
#include "MyEnemy.h"
#include "MyTile.h"
#include "MyPEnemy.h"
#include "HealthPack.h"
#include "world.h"
#include "Game.h"


class MyModel : public QWidget
{
    Q_OBJECT

public:
    MyModel(QWidget *parent = 0);
    ~MyModel();

    int cols;
    int rows;
    float costOfStep = 0.0f;
    MyProtagonist *myProtagonist;
    std::vector<MyTile *> myTilesMap ={};
    std::vector<MyEnemy *> myEnemies ={};
    std::vector<MyPEnemy *> myPEnemies ={};
    std::vector<HealthPack *> myHealthPacks ={};
    bool getWhichView() const;
    void setWhichView(bool value);

public slots:
    //terminal used to show protagonist dead
    void checkHealth();
    void checkEnergy();

private:
    bool whichView = false;

};

#endif // MYMODEL_H
