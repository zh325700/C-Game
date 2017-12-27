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

    bool getAlreadyDefeated() const;
    void setAlreadyDefeated(bool value);

public slots:
private :
    bool alreadyDefeated = false;    // to prevent the protagonist from going back to the defeated but not yet dead PEnemy
};
#endif // MYPENEMY_H
