#include "Health.h"
#include <QFont>

Health::Health(float health):health{health}
{
    // draw the text
    setPlainText(QString("Health: ") + QString::number(health)); // Health: 3
    setDefaultTextColor(Qt::red);
    setFont(QFont("OldEnglish",16));
}
