#include <memory>
#include <QTimer>
#include <memory>
#include <QImage>
#include <QGraphicsTextItem>
#include <iostream>
#include <vector>
#include <QDebug>
#include <typeinfo>
#include <QGraphicsEllipseItem>
#include <QColor>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QGraphicsScene>

#include "Game.h"
#include "Graphics_view_zoom.h"
#include "MainWindow.h"





//in order to use media , you have to add "multimedia" in
//the .pro file

extern MyModel *myModel;

Game::Game(QWidget *parent)
{


    this->rows = myModel->rows;
    this->cols = myModel->cols;
    this->multipleSizeOfCircle =1;
    this->myTilesMap = myModel->myTilesMap;
    this->myEnemies = myModel->myEnemies;
    this->myPEnemies = myModel->myPEnemies;
    this->myHealthPacks = myModel->myHealthPacks;
    ellipse = new QGraphicsEllipseItem();

    // create the scene
    scene = new QGraphicsScene((QGraphicsView *)this);
    scene->setSceneRect(0,0,20000,20000); // make the scene 800x600 instead of infinity by infinity (default)

    // make the newly created scene the scene to visualize (since Game is a QGraphicsView Widget,
    // it can be used to visualize scenes)
    setScene(scene);
    setFixedSize(800,600);

    //create protagonist
    this->myProtagonist = myModel->myProtagonist;
    QObject::connect(this->myProtagonist,SIGNAL(posChanged(int,int)),this->myProtagonist,SLOT(moveToNextSpot()));
    QObject::connect(this->myProtagonist,SIGNAL(posChanged(int,int)),this->myProtagonist,SLOT(aquire_target()));
    QObject::connect(this->myProtagonist,&MyProtagonist::energyChanged,this->myProtagonist,&MyProtagonist::checkProtagonistDead);
    QObject::connect(this->myProtagonist,&MyProtagonist::healthChanged,this->myProtagonist,&MyProtagonist::checkProtagonistDead);


    //set position of the protagonist
    this->myProtagonist->QGraphicsItem::setPos(myProtagonist->getXPos(),myProtagonist->getYPos());
    this->myProtagonist->setFlag(QGraphicsItem::ItemIsFocusable);
    this->myProtagonist->setFocus();


    //add Tiles to the scene and connect
    for(auto &aTile:this->myTilesMap){
        scene->addItem(aTile);
    }
    //add pack to the scene and connect
    for(auto &aPack:this->myHealthPacks){
         scene->addItem(aPack);
    }
    // add the Enemies to the scene
    for(auto &aEnemy:this->myEnemies){
         scene->addItem(aEnemy);
    }

    //add pEnemies to the scene and connect
    for(auto &aPEnemy:this->myPEnemies){
         scene->addItem(aPEnemy);
    }
    // add the protagonist to the scene
    scene->addItem(this->myProtagonist);


    // add the Enemies to the scene and connect // connect enemy signal to Tile slot
    for(auto &aEnemy:this->myEnemies){
         int x=aEnemy->getXPos();
         int y=aEnemy->getYPos();
         QObject::connect(aEnemy,SIGNAL(dead()),myTilesMap[x+y*cols],SLOT(drawBlack()));
    }

    //add pEnemies to the scene and connect
    for(auto &aPEnemy:this->myPEnemies){
         int x=aPEnemy->getXPos();
         int y=aPEnemy->getYPos();
         QObject::connect(aPEnemy,SIGNAL(dead()),this->myTilesMap[x+y*cols],SLOT(drawBlack()));
         QObject::connect(aPEnemy,SIGNAL(dead()),this,SLOT(deletePnemy()));
         QObject::connect(this->myProtagonist,&MyProtagonist::encounterPenemy,this,&Game::drawPoinsonCircle);
         QObject::connect(aPEnemy,&MyPEnemy::poisonLevelUpdated,myProtagonist,&MyProtagonist::ifInPoisonarea);
    }


    //add auto zoom in and out
    Graphics_view_zoom* z = new Graphics_view_zoom(this);
    z->set_modifiers(Qt::NoModifier);
    //show the scene
//    show();
    centerOn(myProtagonist);

    //play background music in a loop
    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/sounds/butterfly.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    QMediaPlayer *music = new QMediaPlayer();
    music->setPlaylist(playlist);
    music->play();
}

Game::~Game()
{
    // delete all memories
}

void Game::drawPoinsonCircle()
{
    //add one circle to the scene the x,y is based on protagoinist current position
    setMultipleSizeOfCircle(2);
    int xCircle = myProtagonist->getXPos() - multipleSizeOfCircle*myProtagonist->getSizeOfTile() ;
    int yCircle = myProtagonist->getYPos() - multipleSizeOfCircle*myProtagonist->getSizeOfTile();
    float widthOfCircle = 2*(0.5 + multipleSizeOfCircle)*myProtagonist->getSizeOfTile();
    float heightOfCircle = widthOfCircle;

    //set brush to the poison circle
    QBrush *brush = new QBrush();
    brush->setStyle(Qt::CrossPattern);
    brush->setColor(Qt::magenta);
    ellipse->setRect(xCircle,yCircle,widthOfCircle,heightOfCircle);
    ellipse->setBrush(*brush);
    scene->addItem(ellipse);
}

void Game::deletePnemy()
{
    QObject* obj = sender();
    MyPEnemy * deadPenemy = dynamic_cast<MyPEnemy *>(sender());
    if(deadPenemy){
        scene->removeItem(deadPenemy);
    //    scene->removeItem(ellipse);
        delete deadPenemy;
    }

}

int Game::getMultipleSizeOfCircle() const
{
    return multipleSizeOfCircle;
}

void Game::setMultipleSizeOfCircle(int value)
{
    multipleSizeOfCircle = value;
}







