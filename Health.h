#ifndef HEALTH_H
#define HEALTH_H
#include <QGraphicsTextItem>

class Health: public QGraphicsTextItem{
public:
    Health(float health);
private:
    float health;
};

#endif // HEALTH_H
