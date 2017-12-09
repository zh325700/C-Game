#include "MainWindow.h"
#include "Game.h"


Game *game;
MainWindow::MainWindow(QWidget * parent):
    QWidget (parent)
{
        game = new Game();
        //create a Horizontal layout to put health and energy
        layout = new QHBoxLayout(this);

        //create health container
        healthLabel = new QLabel("Health:");
        healthValue = new QLineEdit();
        healthValue->setReadOnly(true);
        healthValue->setText(QString::number(game->myProtagonist->getHealth()));


        //create Energy container
        energyLable = new QLabel("Energy:");
        energyValue = new QLineEdit();
        energyValue->setReadOnly(true);
        energyValue->setText(QString::number(game->myProtagonist->getEnergy()));

        //create GroupBox to contain all the label and value
        healthgroup = new QGroupBox("Health show");
        layoutStatistic = new QHBoxLayout(healthgroup);
        layoutStatistic->addWidget(healthLabel);
        layoutStatistic->addWidget(healthValue);
        layoutStatistic->addWidget(energyLable);
        layoutStatistic->addWidget(energyValue);

        layout->addWidget(game);
        layout->addWidget(healthgroup);

        connect(game->myProtagonist,&MyProtagonist::energyChanged,this,&MainWindow::refreshEandH);
        connect(game->myProtagonist,&MyProtagonist::healthChanged,this,&MainWindow::refreshEandH);


}

MainWindow::~MainWindow()
{

}

void MainWindow::refreshEandH()
{
    healthValue->setText(QString::number(game->myProtagonist->getHealth()));
    energyValue->setText(QString::number(game->myProtagonist->getEnergy()));
}
