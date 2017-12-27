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
    QHBoxLayout *boxLayout;
    QLineEdit* xValue;
    QLineEdit* yValue;
    QLineEdit* destinationX;
    QLineEdit* destinationY;
    QLineEdit* aStarParameter;
    QLineEdit* protaSpeed;
    QLineEdit* healthPackNum;
    QLineEdit* enemyNum;
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
   void handleMapButton();
   void autoNavigate();
   void handlePauseButton();
   void handleSoundButton();
signals:
   void pathFound(int speed);

private:
    QPushButton *switch_button;
    QPushButton *start_game_button;
    QPushButton *addNewMap;
    QPushButton *auto_button;
    QPushButton *pause_button;
    QPushButton *soundbutton;

    bool soundOn = true;
};

#endif // MAINWINDOW_H
