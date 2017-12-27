#include "MyPEnemy.h"

MyPEnemy::MyPEnemy(int xPosition, int yPosition, float strength):
    PEnemy(xPosition, yPosition, strength)
{
    int sizeOfTile = 20;
    this->setPos(xPosition*sizeOfTile,yPosition*sizeOfTile);
    setPixmap(QPixmap(":/images/icons/penemy.png"));
}

bool MyPEnemy::getAlreadyDefeated() const
{
    return alreadyDefeated;
}

void MyPEnemy::setAlreadyDefeated(bool value)
{
    alreadyDefeated = value;
}


//MyPEnemy::~PEnemy()
//{

//}
