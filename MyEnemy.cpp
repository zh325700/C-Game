#include "MyEnemy.h"
#include <QGraphicsScene>



MyEnemy::MyEnemy(int xPosition, int yPosition, float strength):
    Enemy(xPosition, yPosition, strength)
{
    int sizeOfTile = 20;
    this->setPos(xPosition*sizeOfTile,yPosition*sizeOfTile);
    setPixmap(QPixmap(":/images/icons/enemy.png"));
}


