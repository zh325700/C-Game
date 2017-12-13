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
//namespace Ui {
//class MainWindow;
//}

class GameTerminal : public QWidget
{
    Q_OBJECT

public:
    explicit GameTerminal(QWidget *parent = 0);
    ~GameTerminal();
    void init();  //inite the help string
    void initWorld();  //init world image
    void setupLayout();  //set up layout
    void uDead();
 //   void newGame();
    bool addHealth(int x, int y);

    //check movable
    bool movePos(QString direction);
    bool movenoWall(QString direction);
    bool moveEnemy(QString direction);
    float totalEnergy(QString direction);
    bool moveEnergy(QString direction);

    //response for command
    void findAllEnemy();
    void findNearEnemy();
    void findAllHealth();
    void findNearHealth();
    QString showProta();

    //event for keyboard
    void keyPressEvent(QKeyEvent *event);

signals:
    void penemyDefeating();

public slots:
    void onEnter();
    void enemyDead();
    void penemyDead();
    void poisonUser(float newLevel);
   // void userDead();

private:
    //layout
    QLineEdit *lineEdit;
    QLabel *indicator;
    QPlainTextEdit *output;
    std::vector<QString> inputs={};
    int inputPosition = 0;

    //world
    int row;
    int col;
    int nrEnemies=5;
    int nrPacks = 5;
    std::vector<MyTile *> aw={};
    std::vector<MyEnemy *> myEnemies ={};
    std::vector<MyPEnemy *> myPEnemies ={};
    std::vector<HealthPack *> myHealthPacks ={};
    MyProtagonist * user;
    //MyProtagonist *myProtagonist;

    //hints string
     const std::type_info& typeEn = typeid(Enemy);
     const std::type_info& typePe = typeid(PEnemy);
     QString helpText;
     QString boundary;
     QString existwall;
     QString existEnemy;
     QString noEnergy;
     int costOfStep = 0;

     //user
     int speed = 1;

};


#endif // GAMETERMINAL_H
