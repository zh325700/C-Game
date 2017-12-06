#include "MyEnemy.h"
#include <QGraphicsScene>



MyEnemy::MyEnemy(int xPosition, int yPosition, float strength):
    Enemy(xPosition, yPosition, strength)
{
    setPixmap(QPixmap(":/images/enemy.png"));
}
