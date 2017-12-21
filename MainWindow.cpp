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

        //create progress bar
        healthbar = new QProgressBar();
        healthbar->setRange(0,100);
        healthbar->setValue(game->myProtagonist->getHealth());
        healthbar->setFormat("The current health is : "+QString::number(game->myProtagonist->getHealth()));

        energtbar = new QProgressBar();
        energtbar->setRange(0,100);
        energtbar->setValue(game->myProtagonist->getEnergy());
        energtbar->setFormat("The current enegy is: "+ QString::number(game->myProtagonist->getEnergy()));


        //create health container
        healthLabel = new QLabel("Health:");


        //create Energy container
        energyLable = new QLabel("Energy:");

        //create GroupBox to contain all the label and value
        healthgroup = new QGroupBox("Health show");
        layoutStatistic = new QVBoxLayout(healthgroup);
        layoutStatistic->addWidget(healthLabel);
        layoutStatistic->addWidget(healthbar);
        layoutStatistic->addWidget(energyLable);
        layoutStatistic->addWidget(energtbar);


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
    healthbar->setValue(game->myProtagonist->getHealth());
    healthbar->setFormat("The current health is : "+QString::number(game->myProtagonist->getHealth()));
    energtbar->setValue(game->myProtagonist->getEnergy());
    energtbar->setFormat("The current enegy is: "+ QString::number(game->myProtagonist->getEnergy()));
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
