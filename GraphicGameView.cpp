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
#include <vector>

#include "GraphicGameView.h"
#include "Graphics_view_zoom.h"
#include "MainWindow.h"





//in order to use media , you have to add "multimedia" in
//the .pro file

extern MyModel *myModel;

GraphicGameView::GraphicGameView(QWidget *parent)
{

    this->setMultipleSizeOfCircle(1);
    ellipse = new QGraphicsEllipseItem();

    // create the scene
    scene = new QGraphicsScene((QGraphicsView *)this);
    scene->setSceneRect(0,0,20000,20000); // make the scene 800x600 instead of infinity by infinity (default)

    // make the newly created scene the scene to visualize (since Game is a QGraphicsView Widget,
    // it can be used to visualize scenes)
    setScene(scene);
    setFixedSize(800,600);

    //create protagonist
//    this->myProtagonist = myModel->myProtagonist;
    // Used to be connect of myProtagonist ~~~~


    //set position of the protagonist
    myModel->myProtagonist->QGraphicsItem::setPos(myModel->myProtagonist->getXPos(),myModel->myProtagonist->getYPos());
    myModel->myProtagonist->setFlag(QGraphicsItem::ItemIsFocusable);
    myModel->myProtagonist->setFocus();


    //add Tiles to the scene and connect
    for(auto &aTile:myModel->myTilesMap){
        scene->addItem(aTile);
    }
    //add pack to the scene and connect
    for(auto &aPack:myModel->myHealthPacks){
         scene->addItem(aPack);
    }
    // add the Enemies to the scene
    for(auto &aEnemy:myModel->myEnemies){
         scene->addItem(aEnemy);
    }

    //add pEnemies to the scene and connect
    for(auto &aPEnemy:myModel->myPEnemies){
         scene->addItem(aPEnemy);
    }
    // add the protagonist to the scene
    scene->addItem(myModel->myProtagonist);


    //make signal and slot connect of Enemies
    for(auto &aEnemy:myModel->myEnemies){
         int x=aEnemy->getXPos();
         int y=aEnemy->getYPos();
         QObject::connect(aEnemy,SIGNAL(dead()),myModel->myTilesMap[x+y*cols],SLOT(drawBlack()));
         QObject::connect(aEnemy,SIGNAL(dead()),this,SLOT(deleteEnemy()));
    }

    //make signal and slot connect of Penemies
    for(auto &aPEnemy:myModel->myPEnemies){
         int x=aPEnemy->getXPos();
         int y=aPEnemy->getYPos();
         QObject::connect(aPEnemy,SIGNAL(dead()),this->myModel->myTilesMap[x+y*cols],SLOT(drawBlack()));
         QObject::connect(aPEnemy,SIGNAL(dead()),this,SLOT(deletePnemy()));
         QObject::connect(myModel->myProtagonist,&MyProtagonist::encounterPenemy,this,&GraphicGameView::drawPoinsonCircle);
         QObject::connect(aPEnemy,&MyPEnemy::poisonLevelUpdated,myModel->myProtagonist,&MyProtagonist::ifInPoisonarea);
    }

    //add auto zoom in and out
    Graphics_view_zoom* z = new Graphics_view_zoom(this);
    z->set_modifiers(Qt::NoModifier);
    //show the scene
//    show();
    centerOn(myModel->myProtagonist);

    //play background music in a loop
    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/sounds/butterfly.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    QMediaPlayer *music = new QMediaPlayer();
    music->setPlaylist(playlist);
    music->play();
}

GraphicGameView::~GraphicGameView()
{
    // delete all memories
}

void GraphicGameView::drawPoinsonCircle()
{
    //add one circle to the scene the x,y is based on protagoinist current position
    setMultipleSizeOfCircle(2);
    int xCircle = myModel->myProtagonist->getXPos()*myModel->myProtagonist->getSizeOfTile() - multipleSizeOfCircle*myModel->myProtagonist->getSizeOfTile() ;
    int yCircle = myModel->myProtagonist->getYPos()*myModel->myProtagonist->getSizeOfTile() - multipleSizeOfCircle*myModel->myProtagonist->getSizeOfTile();
    float widthOfCircle = 2*(0.5 + multipleSizeOfCircle)*myModel->myProtagonist->getSizeOfTile();
    float heightOfCircle = widthOfCircle;

    //set brush to the poison circle
    QBrush *brush = new QBrush();
    brush->setStyle(Qt::CrossPattern);
    brush->setColor(Qt::magenta);
    ellipse->setRect(xCircle,yCircle,widthOfCircle,heightOfCircle);
    ellipse->setBrush(*brush);
    scene->addItem(ellipse);
}

void GraphicGameView::deletePnemy()
{
    MyPEnemy * deadPenemy = dynamic_cast<MyPEnemy *>(sender());
    if(deadPenemy){
        scene->removeItem(deadPenemy);
        delete deadPenemy;
        for(int i=0;i<myModel->myPEnemies.size();i++){
            if(myModel->myPEnemies[i] == deadPenemy){
                myModel->myPEnemies.erase(myModel->myPEnemies.begin()+i);
            }
        }

        qDebug()<<"PEnemy is deleted";
    }
    scene->removeItem(ellipse);


}

void GraphicGameView::deleteEnemy()
{
        MyEnemy *deadEnemy =dynamic_cast<MyEnemy *> (sender());
        if(deadEnemy){
            scene->removeItem(deadEnemy);
            delete deadEnemy;
            for(int i=0;i<myModel->myEnemies.size();i++){
                if(myModel->myEnemies[i] == deadEnemy){
                    myModel->myEnemies.erase(myModel->myEnemies.begin()+i);
                }
            }

            qDebug()<<"Enemy is deleted";
        }

}

int GraphicGameView::getMultipleSizeOfCircle() const
{
    return multipleSizeOfCircle;
}

void GraphicGameView::setMultipleSizeOfCircle(int value)
{
    multipleSizeOfCircle = value;
}








