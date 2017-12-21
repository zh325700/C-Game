#ifndef GAMETERMINAL_H
#define GAMETERMINAL_H

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

class GameTerminal : public QWidget
{
    Q_OBJECT

public:
    explicit GameTerminal(QWidget *parent = 0);
    ~GameTerminal();
    void init();  //inite the help string and other string
    void initWorld();  //init world image
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
    void findAllHealth();
    void findNearHealth();
    QString showProta();

    //event for keyboard
    void keyPressEvent(QKeyEvent *event);

public slots:
    void onEnter();
    void encouterEn();
    void encounterPEn();
    void encouterHe();
    void checkNewPos();
    void enemyDead();
    void penemyDead();
    void poisonUser();
<<<<<<< HEAD
=======

>>>>>>> 4e9f079efac09be2eba90246d416cf2d334f33cc

private:
    //layout
    QLineEdit *lineEdit;
    QPlainTextEdit *output;
    std::vector<QString> inputs={};
    int inputPosition = 0;

    //world
    int rows;
    int cols;
    std::vector<MyTile *> myTilesMap={};
    std::vector<MyEnemy *> myEnemies ={};
    std::vector<MyPEnemy *> myPEnemies ={};
    std::vector<HealthPack *> myHealthPacks ={};
    MyProtagonist * myProtagonist;
    //MyProtagonist *myProtagonist;

    //hints string
     const std::type_info& typeEn = typeid(Enemy);
     const std::type_info& typePe = typeid(PEnemy);
     QString helpText;
     QString boundary;
     QString existwall;
     QString noEnergy;
     int costOfStep = 0;
};


#endif // GAMETERMINAL_H
