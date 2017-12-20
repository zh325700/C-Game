#ifndef MYPENEMY_H
#define MYPENEMY_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsItem>
#include <QMediaPlayer>

#include "world.h"

class MyPEnemy:public PEnemy, public QGraphicsPixmapItem{
public:
    MyPEnemy(int xPosition, int yPosition, float strength);  // allow you yo have a parent point
//    ~PEnemy();
public slots:
private :

};
#endif // MYPENEMY_H
