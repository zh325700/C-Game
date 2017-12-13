#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QWidget>
#include <QGroupBox>
#include <QMessageBox>

#include "MyProtagonist.h"
#include "MyEnemy.h"
#include "MyTile.h"
#include "MyPEnemy.h"
#include "HealthPack.h"
#include "world.h"
#include "Game.h"
#include "GameTerminal.h"

class MainWindow: public QWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent =0);
    ~MainWindow();
    QHBoxLayout *layout;
    QLabel *healthLabel;
    QLineEdit * healthValue;
    QLabel * energyLable;
    QLineEdit* energyValue;
    QGroupBox* healthgroup;
    QHBoxLayout* layoutStatistic;


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
};

#endif // MAINWINDOW_H
