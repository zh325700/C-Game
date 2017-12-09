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
#include "Graphics_view_zoom.h"
#include "MainWindow.h"

//in order to use media , you have to add "multimedia" in
//the .pro file
Game::Game(QWidget *parent){
    std::shared_ptr<World> world = std::make_shared<World>();
    std::vector<std::unique_ptr<Tile>> mapTiles = world->createWorld(":/images/maps/worldmap.png");
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
            QObject::connect(aMyEnemy,SIGNAL(dead()),myTilesMap[xEnemy+yEnemy*cols],SLOT(drawBlack()));// connect enemy signal to Tile slot
            myEnemies.push_back((aMyEnemy));
        }

        //push PEnemies to myPEnemies vector
        else if(typeP.hash_code() == typeUnknow.hash_code()){
            int xPEnemy = unknowEnemy->getXPos();
            int yPEnemy =unknowEnemy->getYPos();
            float pStrength =unknowEnemy->getValue();
            MyPEnemy *aMyPEnemy = new MyPEnemy(xPEnemy,yPEnemy,pStrength); //poisonlevel is strength here
            QObject::connect(aMyPEnemy,SIGNAL(dead()),myTilesMap[xPEnemy+yPEnemy*cols],SLOT(drawPoision()));
            myPEnemies.push_back(aMyPEnemy);
        }

        //if it is not a Enemy, I don't know what to do
        else {
            qDebug() << "No Enemy";
        }
    }

    // create the scene
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,20000,20000); // make the scene 800x600 instead of infinity by infinity (default)

    // make the newly created scene the scene to visualize (since Game is a QGraphicsView Widget,
    // it can be used to visualize scenes)
    setScene(scene);
    setFixedSize(800,600);


    //add Tiles to the scene
    for(auto &aTile:myTilesMap){
        scene->addItem(aTile);
    }
    //add pack to the scene
    for(auto &aPack:myHealthPacks){
         scene->addItem(aPack);
    }

    // add the Enemies to the scene
    for(auto &aEnemy:myEnemies){
         scene->addItem(aEnemy);
    }

    //add pEnemies to the scene
    for(auto &aPEnemy:myPEnemies){
         scene->addItem(aPEnemy);
    }

    //create protagonist
    myProtagonist = new MyProtagonist();
    QObject::connect(myProtagonist,SIGNAL(posChanged(int,int)),myProtagonist,SLOT(moveToNextSpot()));
    QObject::connect(myProtagonist,SIGNAL(posChanged(int,int)),myProtagonist,SLOT(aquire_target()));




    myProtagonist->QGraphicsItem::setPos(myProtagonist->getXPos(),myProtagonist->getYPos());
    myProtagonist->setFlag(QGraphicsItem::ItemIsFocusable);
    myProtagonist->setFocus();


    // add the protagonist to the scene
    scene->addItem(myProtagonist);


    //add auto zoom in and out
    Graphics_view_zoom* z = new Graphics_view_zoom(this);
    z->set_modifiers(Qt::NoModifier);
    //show the scene
    show();
    centerOn(myProtagonist);
}




