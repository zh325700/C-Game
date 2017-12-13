#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <memory>
#include <QObject>

#include "MyEnemy.h"
#include "MyProtagonist.h"
#include "MyTile.h"
#include "MyPEnemy.h"
#include "MyEnemy.h"
#include "HealthPack.h"
#include "MainWindow.h"
#include "world.h"
#include "MyModel.h"

class Game: public QGraphicsView{
    Q_OBJECT
    //give game referance to scene,player,score,health
public:
    Game(QWidget * parent=0);
    ~Game();
    QGraphicsScene * scene;
//    MyEnemy *myEnemy;
    QGraphicsEllipseItem *ellipse;
    int getMultipleSizeOfCircle() const;
    void setMultipleSizeOfCircle(int value);
    MyProtagonist* myProtagonist;
    int cols;
    int rows;

    std::vector<MyTile *> myTilesMap ={};
    std::vector<MyEnemy *> myEnemies ={};
    std::vector<MyPEnemy *> myPEnemies ={};
    std::vector<HealthPack *> myHealthPacks ={};

public slots:
    void drawPoinsonCircle();
    void deletePnemy();

private:
    int multipleSizeOfCircle;
};

#endif // GAME_H