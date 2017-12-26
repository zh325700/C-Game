#include "MainWindow.h"
#include "MyModel.h"


#include <QMessageBox>
#include <QMenuBar>
#include <QFileDialog>




MyModel *myModel;
GraphicGameView *graphicGameView;
TerminalGameView *terminalGameView;

MainWindow::MainWindow(QWidget * parent):
     QWidget(parent)
{

    //  Add toolbar to the mainwindow
        myModel = new MyModel();
        terminalGameView = new TerminalGameView();
        graphicGameView = new GraphicGameView();

        //create a Horizontal layout to show info

        layout = new QGridLayout(this);
        layoutStatistic = new QVBoxLayout();


    //This part not working!!
        boxLayout = new QHBoxLayout(this);

        QMenuBar* menuBar = new QMenuBar();
        QMenu *fileMenu = new QMenu("File");
        menuBar->addMenu(fileMenu);
        fileMenu->addAction("Save");
        fileMenu->addAction("Exit");

        boxLayout->setMenuBar(menuBar);
    //till here



        //create xposition group for prota info
        auto xpositionGroup = new QGroupBox();
        auto layoutX = new QHBoxLayout(xpositionGroup);
        auto xLabel = new QLabel("xPosition : ");
        xValue = new QLineEdit();
        xValue->setText(QString::number(myModel->getMyProtagonist()->getXPos()));
        xValue->setReadOnly(true);
        layoutX->addWidget(xLabel);
        layoutX->addWidget(xValue);

        //create yposition group for prota info
        auto ypositionGroup = new QGroupBox();
        auto layoutY = new QHBoxLayout(ypositionGroup);
        auto yLabel = new QLabel("yPosition : ");
        yValue = new QLineEdit();
        yValue->setReadOnly(true);
        yValue->setText(QString::number(myModel->getMyProtagonist()->getYPos()));
        layoutY->addWidget(yLabel);
        layoutY->addWidget(yValue);

        //create destination x and y  input
        auto dxdyGroup = new QGroupBox();
        auto layoutdx = new QHBoxLayout(dxdyGroup);
        auto dxLabel = new QLabel("xDestination: ");
        destinationX = new QLineEdit();
        layoutdx->addWidget(dxLabel);
        layoutdx->addWidget(destinationX);
        auto dyLabel = new QLabel("yDestination: ");
        destinationY = new QLineEdit();
        layoutdx->addWidget(dyLabel);
        layoutdx->addWidget(destinationY);

        //create Astar parameter
        auto aStarNProtaGroup = new QGroupBox();
        auto layoutANP = new QHBoxLayout(aStarNProtaGroup);
        auto  aStarLabel  =new QLabel("AStar Parameter");
        aStarParameter = new QLineEdit();
        layoutANP -> addWidget(aStarLabel);
        layoutANP -> addWidget(aStarParameter);
        auto protaSpeedLabel = new QLabel("Speed of protagonist (ms)");
        protaSpeed = new QLineEdit();
        layoutANP -> addWidget(protaSpeedLabel);
        layoutANP -> addWidget(protaSpeed);


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
        start_game_button = new QPushButton("Start Game", this);

        addNewMap = new QPushButton("add new map");

        test_button = new QPushButton("test button",this);

        start_game_button->setFixedSize(100,30);
        switch_button->setFixedHeight(30);
        switch_button->setFixedWidth(100);
        auto layoutButtion = new QHBoxLayout();
        layoutButtion->addStretch(1);
        layoutButtion->addWidget(switch_button);
        layoutButtion->addWidget(start_game_button);

        layoutButtion->addWidget(addNewMap);

        layoutButtion->addWidget(test_button);

        layoutButtion->addStretch(1);


        QPixmap openpix("open.png");
        QPixmap quitpix("quit.png");

        layout->addWidget(graphicGameView,0,0,6,1);
        layout->addWidget(terminalGameView,0,0,6,1);
        terminalGameView->hide();                     //by default show graphicView
        layoutStatistic->addWidget(xpositionGroup);
        layoutStatistic->addWidget(ypositionGroup);
        layoutStatistic->addWidget(dxdyGroup);
        layoutStatistic->addWidget(aStarNProtaGroup);
        layoutStatistic->addWidget(healthGroup);
        layoutStatistic->addWidget(energyGroup);
        layoutStatistic->addLayout(layoutButtion);
        layout->addLayout(layoutStatistic,0,1,6,1);
        layout->addLayout(boxLayout,0,2,6,1);


        connect(switch_button, SIGNAL (released()), this, SLOT (handleSwitchButton()));
        connect(start_game_button, SIGNAL (released()), this, SLOT (handleStartButton()));

        connect(addNewMap, SIGNAL (released()), this, SLOT (handleMapButton()));

        connect(test_button,SIGNAL (released()), this, SLOT (autoNavigate()));

        connect(myModel->getMyProtagonist(),&MyProtagonist::posChanged,this,&MainWindow::refreshXandY);
        connect(myModel->getMyProtagonist(),&MyProtagonist::energyChanged,this,&MainWindow::refreshEandH);
        connect(myModel->getMyProtagonist(),&MyProtagonist::healthChanged,this,&MainWindow::refreshEandH);
        connect(myModel->getMyProtagonist(),&MyProtagonist::protagonistDead,this,&MainWindow::restartTheGame);
        connect(graphicGameView,&GraphicGameView::destinationFound,this,&MainWindow::showDestination);
        connect(terminalGameView,&TerminalGameView::destinationFind,this,&MainWindow::showDestination);
        connect(this,&MainWindow::pathFound,graphicGameView,&GraphicGameView::drawThePath);
        connect(myModel->getMyProtagonist(), SIGNAL (findNext()), this, SLOT (autoNavigate()));

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

void MainWindow::refreshXandY()
{
    xValue->setText(QString::number(myModel->getMyProtagonist()->getXPos()));
    yValue->setText(QString::number(myModel->getMyProtagonist()->getYPos()));
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
        delete terminalGameView;
        graphicGameView = new GraphicGameView();
        terminalGameView = new TerminalGameView();
        layout->addWidget(graphicGameView);
        break;
    case QMessageBox::No:
        close();
        break;
    default:
        break;
    }
}

void MainWindow::showDestination()
{

    if(myModel->getWhichView()){
        destinationX->setText(QString::number(terminalGameView->getDX()));
        destinationY->setText(QString::number(terminalGameView->getDY()));
    }
    else{
        destinationX->setText(QString::number(graphicGameView->getEndPoint().x()));
        destinationY->setText(QString::number(graphicGameView->getEndPoint().y()));
    }
}

void MainWindow::handleSwitchButton()
{
    myModel->setWhichView(!myModel->getWhichView());
    bool whichView = myModel->getWhichView();
    if(whichView){
        terminalGameView->show();
        graphicGameView->hide();
    }
    else{
        terminalGameView->hide();
        graphicGameView->show();
    }
}

void MainWindow::handleStartButton()
{
    //Model get the destination x and y , false is graphicView , true is terinalView
    bool whichView = myModel->getWhichView();
    if(whichView){
                        //xuqingji de fangfa lai nadao x,y
        myModel->setDestinationX(22);
        myModel->setDestinationY(22);
    }
    else{
        myModel->setDestinationX(round((destinationX->text()).toDouble()));
        myModel->setDestinationY(round((destinationY->text()).toDouble()));
        qDebug()<<"Model destination X:"<<myModel->getDestinationX();
        qDebug()<<"Model destination Y:"<<myModel->getDestinationY();

    }

    if(myModel->moveFast()){
        //MyModel *tempM = myModel;    //for testing purpose
        emit pathFound(round((protaSpeed->text()).toInt()));
    }else{
        qDebug()<<"Can not find the path";
    }

    //Here the pathfinding game start.
}


void MainWindow::handleMapButton()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,
        tr("Open Image"), "/home", tr("Image Files (*.png *.jpg *.bmp)"));
    qDebug()<<fileName;
    graphicGameView->scene->clear();
    delete myModel;
    myModel = new MyModel(fileName,50,500);
}

void MainWindow::autoNavigate()
{
    myModel->FindNextStep();
    emit pathFound(round((protaSpeed->text()).toInt()));
}
