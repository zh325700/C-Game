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
#include <QString>

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

    QString getCurrentFileName() const;
    void setCurrentFileName(const QString &value);
    void removeEveryFromTheScene();
public slots:
    void refreshEandH();
    void refreshXandY();
    void restartTheGame();


private slots:

   void handleSwitchButton();
   void handleStartButton();
   void handleMapButton();
   void autoNavigate();
   void handlePauseButton();
   void handleSaveButton();
   void handleLoadButton();
signals:
   void pathFound(int speed);

private:
   void reset();
   void gameSetting();

   QPushButton *switch_button;
   QPushButton *start_game_button;
   QPushButton *chooseNewMap;
   QPushButton *auto_button;
   QPushButton *pause_button;
   QPushButton *save_button;
   QPushButton *load_button;

    bool soundOn = true;
    QString currentFileName = ":/images/maps/worldmap.png";
};

#endif // MAINWINDOW_H
