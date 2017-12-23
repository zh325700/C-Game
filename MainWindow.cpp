#include "MainWindow.h"
#include "MyModel.h"


#include <QMessageBox>




MyModel *myModel;
TerminalGameView *terminalGameView;
GraphicGameView *graphicGameView;

MainWindow::MainWindow(QWidget * parent):
    QWidget (parent)
{

        myModel = new MyModel();
        terminalGameView = new TerminalGameView();
        graphicGameView = new GraphicGameView();
        //terminalGameView = new TerminalGameView();

        //create a Horizontal layout to show info
        layout = new QHBoxLayout(this);
        layoutStatistic = new QVBoxLayout();

        //create health group for health info
        healthGroup = new QGroupBox();
        layoutHealth = new QHBoxLayout(healthGroup);
        healthLabel = new QLabel("Health:");
        //create progress bar
        healthbar = new QProgressBar();
        healthbar->setRange(0,100);

        healthbar->setValue(myModel->getMyProtagonist()->getHealth());
        healthbar->setFormat("The current health is : "+QString::number(myModel->getMyProtagonist()->getHealth()));
        //healthbar->setAlignment(Qt::AlignCenter);
        healthbar->setStyleSheet("::chunk{background-color: red;border: 2px solid black;border-radius: 5px;text-align: center;}");
        layoutHealth->addWidget(healthLabel);
        layoutHealth->addWidget(healthbar);

        //create a energy group for energy info
        energyGroup = new QGroupBox();
        layoutEnergy = new QHBoxLayout(energyGroup);
        energyLabel = new QLabel("Energy:");

        energtbar = new QProgressBar();
        //create progress bar
        energtbar->setRange(0,100);

        energtbar->setValue(myModel->getMyProtagonist()->getEnergy());
        energtbar->setFormat("The current enegy is: "+ QString::number(myModel->getMyProtagonist()->getEnergy()));
        energtbar->setStyleSheet("::chunk{background-color: yellow;border: 2px solid black;border-radius: 5px;text-align: center;}");
        layoutEnergy->addWidget(energyLabel);
        layoutEnergy->addWidget(energtbar);

        //button
        switch_button = new QPushButton("Switch View", this);
        switch_button->setFixedHeight(30);
        switch_button->setFixedWidth(100);
        auto layoutButtion = new QHBoxLayout();
        layoutButtion->addStretch(1);
        layoutButtion->addWidget(switch_button);
        layoutButtion->addStretch(1);

        //layout->addWidget(graphicGameView);
        layout->addWidget(terminalGameView);
        layout->addWidget(graphicGameView);
        graphicGameView->hide();
        layoutStatistic->addWidget(healthGroup);
        layoutStatistic->addWidget(energyGroup);
        layoutStatistic->addLayout(layoutButtion);
        layout->addLayout(layoutStatistic);


        connect(switch_button, SIGNAL (released()), this, SLOT (handleButton()));
        connect(myModel->getMyProtagonist(),&MyProtagonist::energyChanged,this,&MainWindow::refreshEandH);
        connect(myModel->getMyProtagonist(),&MyProtagonist::healthChanged,this,&MainWindow::refreshEandH);
        connect(myModel->getMyProtagonist(),&MyProtagonist::protagonistDead,this,&MainWindow::restartTheGame);


}

MainWindow::~MainWindow()
{
    //deal with memory
}



void MainWindow::refreshEandH()
{
    healthbar->setValue(myModel->getMyProtagonist()->getHealth());
    healthbar->setFormat("The current health is : "+QString::number(myModel->getMyProtagonist()->getHealth()));
    energtbar->setValue(myModel->getMyProtagonist()->getEnergy());
    energtbar->setFormat("The current enegy is: "+ QString::number(myModel->getMyProtagonist()->getEnergy()));
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
        terminalGameView->hide();
        graphicGameView->show();
    }
    else{
        terminalGameView->show();
        graphicGameView->hide();
    }
}
