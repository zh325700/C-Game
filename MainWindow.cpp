#include "MainWindow.h"
#include "MyModel.h"


#include <QMessageBox>
#include <QMenuBar>
#include <QFileDialog>
#include <QStateMachine>
#include <QState>
#include <QInputDialog>




MyModel *myModel;
GraphicGameView *graphicGameView;
TerminalGameView *terminalGameView;

MainWindow::MainWindow(QWidget * parent):
    QWidget(parent)
{
    //  Add toolbar to the mainwindow
    myModel = new MyModel(currentFileName);
    gameSetting();
    myModel->modelInitialize();
    terminalGameView = new TerminalGameView();
    graphicGameView = new GraphicGameView();

    //create a Horizontal layout to show info

    layout = new QGridLayout(this);
    layoutStatistic = new QVBoxLayout();


    //create xposition group for prota info
    auto xpositionGroup = new QGroupBox();
    auto layoutX = new QHBoxLayout(xpositionGroup);
    auto xLabel = new QLabel("xPosition : ");
    xValue = new QLineEdit();
    xValue->setReadOnly(true);
    layoutX->addWidget(xLabel);
    layoutX->addWidget(xValue);

    //create yposition group for prota info
    auto ypositionGroup = new QGroupBox();
    auto layoutY = new QHBoxLayout(ypositionGroup);
    auto yLabel = new QLabel("yPosition : ");
    yValue = new QLineEdit();
    yValue->setReadOnly(true);
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
    energtbar->setStyleSheet("::chunk{background-color: yellow;border: 2px solid black;border-radius: 5px;text-align: center;}");
    layoutEnergy->addWidget(energyLabel);
    layoutEnergy->addWidget(energtbar);

    //prepare button image
    QPixmap startPix(":/images/icons/startGameIcon.png");
    QIcon startGameIcon(startPix);


    //button
    switch_button = new QPushButton("Switch View", this);
    start_game_button = new QPushButton("Start Game", this);
    start_game_button->setIcon(startGameIcon);
    chooseNewMap = new QPushButton("choose a new map");
    auto_button = new QPushButton("auto run",this);
    pause_button = new QPushButton("Pause",this);

    start_game_button->setFixedSize(100,30);
    switch_button->setFixedHeight(30);
    switch_button->setFixedWidth(100);
    auto layoutButton = new QHBoxLayout();
    //add button to layout
    layoutButton->addStretch(1);
    layoutButton->addWidget(switch_button);
    layoutButton->addWidget(start_game_button);
    layoutButton->addWidget(chooseNewMap);
    layoutButton->addWidget(auto_button);
    layoutButton->addWidget(pause_button);
    layoutButton->addStretch(1);

    //add all widget to overall layout
    layoutStatistic->addWidget(xpositionGroup);
    layoutStatistic->addWidget(ypositionGroup);
    layoutStatistic->addWidget(dxdyGroup);
    layoutStatistic->addWidget(aStarNProtaGroup);
    layoutStatistic->addWidget(healthGroup);
    layoutStatistic->addWidget(energyGroup);
    layoutStatistic->addLayout(layoutButton);


    // connect button
    connect(switch_button, SIGNAL (released()), this, SLOT (handleSwitchButton()));
    connect(start_game_button, SIGNAL (released()), this, SLOT (handleStartButton()));
    connect(chooseNewMap, SIGNAL (released()), this, SLOT (handleMapButton()));
    connect(auto_button,SIGNAL (released()), this, SLOT (autoNavigate()));
    connect(pause_button,SIGNAL (released()), this, SLOT (handlePauseButton()));

    reset();
    layout->addLayout(layoutStatistic,0,1,6,1);
}

void MainWindow::reset()
{
    xValue->setText(QString::number(myModel->getMyProtagonist()->getXPos()));
    yValue->setText(QString::number(myModel->getMyProtagonist()->getYPos()));

    healthbar->setValue(myModel->getMyProtagonist()->getHealth());
    healthbar->setFormat("The current health is : "+QString::number(myModel->getMyProtagonist()->getHealth()));

    energtbar->setValue(myModel->getMyProtagonist()->getEnergy());
    energtbar->setFormat("The current enegy is: "+ QString::number(myModel->getMyProtagonist()->getEnergy()));

    aStarParameter->setText(QString::number(myModel->getW()));

    //connect signal and slot
    connect(myModel->getMyProtagonist(),&MyProtagonist::posChanged,this,&MainWindow::refreshXandY);
    connect(myModel->getMyProtagonist(),&MyProtagonist::energyChanged,this,&MainWindow::refreshEandH);
    connect(myModel->getMyProtagonist(),&MyProtagonist::healthChanged,this,&MainWindow::refreshEandH);
    connect(myModel->getMyProtagonist(),&MyProtagonist::protagonistDead,this,&MainWindow::restartTheGame);
    connect(this,&MainWindow::pathFound,graphicGameView,&GraphicGameView::drawThePath);
    connect(myModel->getMyProtagonist(), SIGNAL (findNext()), this, SLOT (autoNavigate()));

    layout->addWidget(graphicGameView,0,0,6,1);
    layout->addWidget(terminalGameView,0,0,6,1);
    terminalGameView->hide();                     //by default show graphicView


}

void MainWindow::gameSetting()
{
    bool enemyOK;
    int i = QInputDialog::getInt(this, tr("Enemies"),
                                 tr("Choose the number of enemies:"), 50, 0, 100, 1, &enemyOK);
    if (enemyOK) myModel->setNrOfEnemies(i);

    bool healthpackOK;
    int j = QInputDialog::getInt(this, tr("HealthPacks"),
                                 tr("Choose the number of healthpacks:"), 500, 0, 1000, 1, &healthpackOK);
    if (enemyOK) myModel->setNrOfHealthPacks(j);
}

QString MainWindow::getCurrentFileName() const
{
    return currentFileName;
}

void MainWindow::setCurrentFileName(const QString &value)
{
    currentFileName = value;
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
        delete myModel;
        delete terminalGameView;
        delete graphicGameView;
        myModel = new MyModel(currentFileName);
        gameSetting();
        myModel->modelInitialize();
        terminalGameView = new TerminalGameView();
        graphicGameView = new GraphicGameView();
        reset();
        break;
    case QMessageBox::No:
        close();
        break;
    default:
        break;
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
        //        qDebug()<<"Model destination X:"<<myModel->getDestinationX();
        //        qDebug()<<"Model destination Y:"<<myModel->getDestinationY();

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
    hide();
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,
                                            tr("Open Image"), "/home", tr("Image Files (*.png *.jpg *.bmp)"));
    qDebug()<<fileName;
    if(fileName != NULL)
    {
        delete myModel;
        delete terminalGameView;
        delete graphicGameView;
        setCurrentFileName(fileName);
        myModel = new MyModel(fileName);
        gameSetting();
        myModel->modelInitialize();
        terminalGameView = new TerminalGameView();
        graphicGameView = new GraphicGameView();
        reset();
        show();
        QMessageBox::information(this,"Success","Congratulations! New map is ready to use! :)",true);
    }

}

void MainWindow::autoNavigate()
{
    myModel->setW((aStarParameter->text()).toFloat());
    myModel->FindNextStep();
    qDebug()<<"w is: "<<myModel->getW();
    emit pathFound(round((protaSpeed->text()).toInt()));
}

void MainWindow::handlePauseButton()
{
    myModel->getMyProtagonist()->setPaused(!myModel->getMyProtagonist()->getPaused());
}




