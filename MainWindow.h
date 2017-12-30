#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QWidget>
#include <QMainWindow>
#include <QGroupBox>
#include <QMessageBox>
#include <QPushButton>
#include <QProgressBar>
#include <QString>
#include <string>
#include <vector>
#include <QComboBox>

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
    QComboBox *protaSpeed;
    QLineEdit* healthPackNum;
    QLineEdit* enemyNum;
    QProgressBar *healthbar ;
    QProgressBar *energtbar;

    MainWindow(QWidget *parent =0);
    ~MainWindow();

    void reset();

    /*used to ask for number of enemies and healthpacks before game*/
    void gameSetting();

    /*used in loading record function to remove all the items*/
    void removeEveryItemFromTheScene();

    /*getters and setters*/
    QString getCurrentFileName() const;
    void setCurrentFileName(const QString &value);

public slots:
    void refreshEandH();
    void refreshXandY();
    void restartTheGame();


private slots:

    void handleSwitchButton();
    void showSpeedChanged();
    void handleSpeed(int idx);
    void handleStartButton();
    void handleMapButton();
    void handleW();
    void showWChanged();
    void autoNavigate();
    void handlePauseButton();
    void handleSaveButton();
    void handleLoadButton();
    void handleAddHealthpackButton();
    void handleClearAllFilesButton();
    void switchLayout();

signals:
    void pathFound();
    void speedChanged();

private:
    QHBoxLayout *layoutButton;
    QHBoxLayout *layoutSaveNload;
    QPushButton *switch_button;
    QPushButton *start_game_button;
    QPushButton *chooseNewMap;
    QPushButton *auto_button;
    QPushButton *pause_button;
    QPushButton *save_button;
    QPushButton *load_button;
    QPushButton *addHealthpack_button;
    QPushButton *clearAllFiles_button;

    QString currentFileName = ":/images/maps/worldmap.png";

    std::vector<QString> saveFileNames;
};

#endif // MAINWINDOW_H
