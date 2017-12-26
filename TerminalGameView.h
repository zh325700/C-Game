#ifndef TERMINALGAMEVIEW_H
#define TERMINALGAMEVIEW_H

#include <QMainWindow>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QGraphicsView>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QLabel>
#include <QGroupBox>
#include <QObject>
#include <QKeyEvent>
#include <typeinfo>
#include <QtMath>

#include "world.h"
#include "MyEnemy.h"
#include "MyTile.h"
#include "MyPEnemy.h"
#include "HealthPack.h"
#include "MyProtagonist.h"

using namespace std;

class TerminalGameView : public QWidget
{
    Q_OBJECT

public:
    explicit TerminalGameView(QWidget *parent = 0);
    ~TerminalGameView();
    void init();  //inite the help string and other string
    void setupLayout();  //set up layout

    //check enemy warning
    void moveEnemy();
    bool moveHealth(int x, int y);

    //terminal check movable
    bool movePos(QString direction);
    bool movenoWall(QString direction);

    //response for command
    void findAllEnemy();
    void findNearEnemy();
    int countNearEnemy();
    void findAllHealth();
    void findNearHealth();
    int countNearHealth();
    QString showProta();

    //event for keyboard
    void keyPressEvent(QKeyEvent *event);

    int getDX() const;
    void setDX(int value);

    int getDY() const;
    void setDY(int value);

signals:
    void destinationFind();

public slots:
    void onEnter();
    void encouterEn();
    void encounterPEn();
    void encouterHe();
    void checkNewPos();
    void enemyDead();
    void penemyDead();
    void poisonUser();

private:
    //layout
    QLineEdit *lineEdit;
    QPlainTextEdit *output;
    QFont font=QFont("CodeNewRoman");
    std::vector<QString> inputs={};
    unsigned inputPosition = 0;

    //hints string
     const std::type_info& typeEn = typeid(Enemy);
     const std::type_info& typePe = typeid(PEnemy);
     QString helpText;
     QString boundary;
     QString existwall;
     QString noEnergy;
     int costOfStep = 0;
     int dX=0;
     int dY=0;
};


#endif // TERMINALGAMEVIEW_H
