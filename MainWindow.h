#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
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
    QGridLayout *layout;
    QLabel *healthLabel;
    QLabel * energyLabel;
    QGroupBox* healthGroup;
    QHBoxLayout* layoutHealth;
    QGroupBox* energyGroup;
    QHBoxLayout* layoutEnergy;
    QVBoxLayout* layoutStatistic;
    QLineEdit* xValue;
    QLineEdit* yValue;
    QLineEdit* destinationX;
    QLineEdit* destinationY;
    QProgressBar *healthbar ;
    QProgressBar *energtbar;

public slots:
    void refreshEandH();
    void refreshXandY();
    void restartTheGame();
    void showDestination();

private slots:
   void handleSwitchButton();
   void handleStartButton();

private:
    QPushButton *switch_button;
    QPushButton *start_game_button;

};

#endif // MAINWINDOW_H
