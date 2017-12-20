#include "MainWindow.h"
#include "MyModel.h"


#include <QMessageBox>


Game *game;
MyModel *myModel;
GameTerminal *gameTerminal;

MainWindow::MainWindow(QWidget * parent):
    QWidget (parent)
{

        myModel = new MyModel();
        game = new Game();
        gameTerminal = new GameTerminal();
        switch_button = new QPushButton("Switch View", this);


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
        layoutStatistic = new QVBoxLayout(healthgroup);
        layoutStatistic->addWidget(healthLabel);
        layoutStatistic->addWidget(healthValue);
        layoutStatistic->addWidget(energyLable);
        layoutStatistic->addWidget(energyValue);

        //layout->addWidget(game);
        layout->addWidget(gameTerminal);
        layout->addWidget(game);
        game->hide();
        layout->addWidget(healthgroup);
        layout->addWidget(switch_button);

        connect(switch_button, SIGNAL (released()), this, SLOT (handleButton()));
        connect(game->myProtagonist,&MyProtagonist::energyChanged,this,&MainWindow::refreshEandH);
        connect(game->myProtagonist,&MyProtagonist::healthChanged,this,&MainWindow::refreshEandH);
        connect(game->myProtagonist,&MyProtagonist::protagonistDead,this,&MainWindow::restartTheGame);


}

MainWindow::~MainWindow()
{
    //deal with memory
}



void MainWindow::refreshEandH()
{
    healthValue->setText(QString::number(game->myProtagonist->getHealth()));
    energyValue->setText(QString::number(game->myProtagonist->getEnergy()));
}

void MainWindow::restartTheGame()   // Yes: clean all memory and restart a game, No: close the window
{
    int result = QMessageBox::warning(this, tr("My Game"),
                                   tr("You Are Dead.\n"
                                      "Do you want to play agin?"),
                                   QMessageBox::Yes | QMessageBox::No);
    switch (result) {
    case QMessageBox::Yes:
        delete game;
        game = new Game();
        layout->addWidget(game);
        break;
    case QMessageBox::No:
        close();
        break;
    default:
        break;
    }
}

void MainWindow::handleButton()
{
    myModel->setWhichView(!myModel->getWhichView());
    bool whichView = myModel->getWhichView();
    if(whichView){
        gameTerminal->hide();
        game->show();
    }
    else{
        gameTerminal->show();
        game->hide();
    }
}
