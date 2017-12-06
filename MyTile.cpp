#include "MyTile.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QBrush>
#include <QRect>

MyTile::MyTile(int xPosition, int yPosition, float tileWeight):
    Tile(xPosition, yPosition, tileWeight)
{
//    if(tileWeight<0.5){
//        this->setPos(xPosition*20,yPosition*20);
//        setPixmap(QPixmap(":/images/enemy.png"));
//    }
//    else {
//        setPixmap(QPixmap(":/images/enemy.png"));
//    }
//    qDebug() <<value;


 this->setRect(xPos*20,yPos*20,20,20);
 if(value<0.8){
     QBrush brush(Qt::gray, Qt::SolidPattern);
     this->setBrush(brush);
 }
 else if(value<=1 && value>0.8){
    QBrush brush(Qt::white, Qt::SolidPattern);
    this->setBrush(brush);
 }
 else {
     QBrush brush(Qt::black, Qt::SolidPattern);
     this->setBrush(brush);
 }

}


