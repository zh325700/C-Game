#ifndef MYPROTAGONIST_H
#define MYPROTAGONIST_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsItem>
#include <QMediaPlayer>
#include <vector>

#include "world.h"
#include "MyTile.h"

class MyProtagonist:public Protagonist, public QGraphicsPixmapItem{
    Q_OBJECT  // if you want to have signal and slot you have to be a QObject
public:
    MyProtagonist(QGraphicsItem * parent=0);  // allow you yo have a parent point
    void keyPressEvent(QKeyEvent * event);
    float getNextSpotValue(int x,int y, std::vector<MyTile *> &myTiles,int &world_cols);
public slots:
    void moveToNextSpot();
private :
    void decreaseHealth(float health_value);
    void increaseHealth(float health_value);

};


#endif // MYPROTAGONIST_H
