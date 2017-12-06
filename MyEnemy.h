#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsItem>
#include <QMediaPlayer>

#include "world.h"

class MyEnemy:public Enemy, public QGraphicsPixmapItem{
public:
    MyEnemy(int xPosition, int yPosition, float strength);  // allow you yo have a parent point
public slots:
private :

};


#endif
