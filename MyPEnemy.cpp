#include "MyPEnemy.h"

MyPEnemy::MyPEnemy(int xPosition, int yPosition, float strength):
    PEnemy(xPosition, yPosition, strength)
{
setPixmap(QPixmap(":/images/enemy.png"));
}
