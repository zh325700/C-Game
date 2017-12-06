
#include <memory>
#include <QTimer>
#include "MyEnemy.h"
#include <memory>
#include <QImage>
#include <QGraphicsTextItem>
#include <iostream>
#include <vector>
#include <QDebug>
#include <typeinfo>

#include "HealthPack.h"
#include "world.h"
#include "Game.h"
#include "MyProtagonist.h"

//in order to use media , you have to add "multimedia" in
//the .pro file

Game::Game(QWidget *parent){
    std::shared_ptr<World> world = std::make_shared<World>();
    std::vector<std::unique_ptr<Tile>> mapTiles = world->createWorld(":/images/worldmap.png");
    std::vector<std::unique_ptr<Tile>> healthpacks = world->getHealthPacks(500);
    std::vector<std::unique_ptr<Enemy>> enemiesFromWorld = world->getEnemies(50);
    const std::type_info& typeE = typeid(Enemy);
    const std::type_info& typeP = typeid(PEnemy);


    cols = world->getCols();
    rows = world->getRows();

    // Give all the world tiles in Mymaptiles
    for ( auto &aTile: mapTiles){
        //Create MyTile class to be able to show the tiles
        int xPosition =aTile->getXPos();
        int yPositinon =aTile->getYPos();
        float blood =aTile->getValue();
        MyTile* aMyTile =new MyTile(xPosition,yPositinon,blood);        //Game have a vector of MyTile
        myTilesMap.push_back(aMyTile);                  //loop vector of MyTile through and add them to the scene
    }

    // Give all the Healthpacks in Myhealthpacks
    for(auto &aPack: healthpacks){
        int xhealth =aPack->getXPos();
        int yhealth =aPack->getYPos();
        float uselessValue =aPack->getValue();
        HealthPack *aMyHealthPack = new HealthPack(xhealth,yhealth,uselessValue);  //unexpected finished
        myHealthPacks.push_back(aMyHealthPack);
    }

    // judge what enemy type it is and copy its value to myEnemies and myPEnemies accordingly
    for(auto &unknowEnemy: enemiesFromWorld){
        const std::type_info& typeUnknow = typeid(*unknowEnemy);   //have to be * , I don't know why

        //push Enemies to myEnemies vector
        if(typeE.hash_code() == typeUnknow.hash_code()){
            int xEnemy = unknowEnemy->getXPos();
            int yEnemy =unknowEnemy->getYPos();
            float eStrength =unknowEnemy->getValue();
            MyEnemy *aMyEnemy = new MyEnemy(xEnemy,yEnemy,eStrength); //defeated is by default false, no need to pass
            myEnemies.push_back((aMyEnemy));
        }

        //push PEnemies to myPEnemies vector
        else if(typeP.hash_code() == typeUnknow.hash_code()){
            int xPEnemy = unknowEnemy->getXPos();
            int yPEnemy =unknowEnemy->getYPos();
            float pStrength =unknowEnemy->getValue();
            MyEnemy *aMyPEnemy = new MyEnemy(xPEnemy,yPEnemy,pStrength); //poisonlevel is strength here
            myPEnemies.push_back((aMyPEnemy));
        }

        //if it is not a Enemy, I don't know what to do
        else {
            qDebug() << "No Enemy";
        }
    }

    // create the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,20000,20000); // make the scene 800x600 instead of infinity by infinity (default)

    // make the newly created scene the scene to visualize (since Game is a QGraphicsView Widget,
    // it can be used to visualize scenes)
    setScene(scene);
    //    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,600);


    //add Tiles to the scene
    for(auto &aTile:myTilesMap){
        scene->addItem(aTile);
    }
    //add pack to the scene
    for(auto &aPack:myHealthPacks){
         scene->addItem(aPack);
    }

    // create the enemy
    myEnemy = new MyEnemy(250,250,10.0);
    myEnemy->setPos(myEnemy->getXPos(),myEnemy->getYPos());

    // add the Enemy to the scene
    scene->addItem(myEnemy);

    //create protagonist
    myProtagonist = new MyProtagonist();
    QObject::connect(myProtagonist,SIGNAL(posChanged(int,int)),myProtagonist,SLOT(moveToNextSpot()));
    myProtagonist->QGraphicsItem::setPos(myProtagonist->getXPos(),myProtagonist->getYPos());
    myProtagonist->setFlag(QGraphicsItem::ItemIsFocusable);
    myProtagonist->setFocus();

    // add the protagonist to the scene
    scene->addItem(myProtagonist);

    //show the scene
    show();
}
