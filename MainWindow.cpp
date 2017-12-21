#include "MainWindow.h"
#include "MyModel.h"


#include <QMessageBox>



GraphicGameView *graphicGameView;
MyModel *myModel;
GameTerminal *gameTerminal;

MainWindow::MainWindow(QWidget * parent):
    QWidget (parent)
{

        myModel = new MyModel();
        graphicGameView = new GraphicGameView();
        gameTerminal = new GameTerminal();
        switch_button = new QPushButton("Switch View", this);


        //create a Horizontal layout to put health and energy
        layout = new QHBoxLayout(this);

        //create progress bar
        healthbar = new QProgressBar();
        healthbar->setRange(0,100);
        healthbar->setValue(graphicGameView->myProtagonist->getHealth());
        healthbar->setFormat("The current health is : "+QString::number(graphicGameView->myProtagonist->getHealth()));

        energtbar = new QProgressBar();
        energtbar->setRange(0,100);
        energtbar->setValue(graphicGameView->myProtagonist->getEnergy());
        energtbar->setFormat("The current enegy is: "+ QString::number(graphicGameView->myProtagonist->getEnergy()));


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


        //layout->addWidget(graphicGameView);
        layout->addWidget(gameTerminal);
        layout->addWidget(graphicGameView);
        graphicGameView->hide();
        layout->addWidget(healthgroup);
        layout->addWidget(switch_button);

        connect(switch_button, SIGNAL (released()), this, SLOT (handleButton()));
        connect(graphicGameView->myProtagonist,&MyProtagonist::energyChanged,this,&MainWindow::refreshEandH);
        connect(graphicGameView->myProtagonist,&MyProtagonist::healthChanged,this,&MainWindow::refreshEandH);
        connect(graphicGameView->myProtagonist,&MyProtagonist::protagonistDead,this,&MainWindow::restartTheGame);


}

MainWindow::~MainWindow()
{
    //deal with memory
}



void MainWindow::refreshEandH()
{
    healthbar->setValue(graphicGameView->myProtagonist->getHealth());
    healthbar->setFormat("The current health is : "+QString::number(graphicGameView->myProtagonist->getHealth()));
    energtbar->setValue(graphicGameView->myProtagonist->getEnergy());
    energtbar->setFormat("The current enegy is: "+ QString::number(graphicGameView->myProtagonist->getEnergy()));
}

void MainWindow::restartTheGame()   // Yes: clean all memory and restart a game, No: close the window
{
    int result = QMessageBox::warning(this, tr("My Game"),
                                   tr("You Are Dead.\n"
                                      "Do you want to play agin?"),
                                   QMessageBox::Yes | QMessageBox::No);
    switch (result) {
    case QMessageBox::Yes:
        delete graphicGameView;
        graphicGameView = new GraphicGameView();
        layout->addWidget(graphicGameView);
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
        graphicGameView->show();
    }
    else{
        gameTerminal->show();
        graphicGameView->hide();
    }
}
