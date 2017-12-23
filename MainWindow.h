#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QWidget>
#include <QGroupBox>
#include <QMessageBox>
#include <QPushButton>
#include <QProgressBar>

#include "MyProtagonist.h"
#include "MyEnemy.h"
#include "MyTile.h"
#include "MyPEnemy.h"
#include "HealthPack.h"
#include "world.h"
#include "GraphicGameView.h"
#include "TerminalGameView.h"

class MainWindow: public QWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent =0);
    ~MainWindow();
    QHBoxLayout *layout;
    QLabel *healthLabel;
    QLabel * energyLabel;
    QGroupBox* healthGroup;
    QHBoxLayout* layoutHealth;
    QGroupBox* energyGroup;
    QHBoxLayout* layoutEnergy;
    QVBoxLayout* layoutStatistic;
    QProgressBar *healthbar ;
    QProgressBar *energtbar;


    //new added
//    int cols;
//    int rows;
//    MyProtagonist *myProtagonist;
//    std::vector<MyTile *> myTilesMap ={};
//    std::vector<MyEnemy *> myEnemies ={};
//    std::vector<MyPEnemy *> myPEnemies ={};
//    std::vector<HealthPack *> myHealthPacks ={};


public slots:
    void refreshEandH();
    void restartTheGame();

private slots:
   void handleButton();

private:
    QPushButton *switch_button;

};

#endif // MAINWINDOW_H
