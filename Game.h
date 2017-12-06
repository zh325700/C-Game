#ifndef GAME_H
#define GAME_H
/*
-Create resource file
-QMediaPlayer,setMedia,QUrl,play()
*/
#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <memory>

#include "MyEnemy.h"
#include "MyProtagonist.h"
#include "MyTile.h"
#include "MyPEnemy.h"
#include "MyEnemy.h"
#include "HealthPack.h"

class Game: public QGraphicsView{
    //give game referance to scene,player,score,health
public:
    Game(QWidget * parent=0);
    QGraphicsScene * scene;
    MyEnemy *myEnemy;
    MyProtagonist *myProtagonist;
    int cols;
    int rows;
    std::vector<MyTile *> myTilesMap ={};
    std::vector<MyEnemy *> myEnemies ={};
    std::vector<MyPEnemy *> myPEnemies ={};
    std::vector<HealthPack *> myHealthPacks ={};

};

#endif // GAME_H
