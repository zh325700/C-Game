#include "MainWindow.h"
#include "MyModel.h"


#include <QMessageBox>
#include <QMenuBar>
#include <QFileDialog>
#include <QStateMachine>
#include <QState>
#include <QInputDialog>
#include <QDateTime>
#include <QStringList>
#include <QFileInfo>
#include <QStandardPaths>
#include "Customdialog.h"




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
    graphicGameView->initialGraphicView();

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
    start_game_button = new QPushButton("Move to", this);
    start_game_button->setIcon(startGameIcon);
    chooseNewMap = new QPushButton("Choose a new map");
    auto_button = new QPushButton("Auto run",this);
    pause_button = new QPushButton("Pause",this);
    save_button = new QPushButton("Save",this);
    load_button = new QPushButton("Load",this);
    clearAllFiles_button = new QPushButton("Clear Save",this);
    addHealthpack_button = new QPushButton("Add Healthpack",this);

    start_game_button->setFixedSize(100,30);
    switch_button->setFixedHeight(30);
    switch_button->setFixedWidth(100);
    auto layoutButton = new QHBoxLayout();
    auto layoutSaveNload = new QHBoxLayout();
    //add button to layout
    layoutButton->addStretch(1);
    layoutButton->addWidget(switch_button);
    layoutButton->addWidget(start_game_button);
    layoutButton->addWidget(chooseNewMap);
    layoutButton->addWidget(auto_button);
    layoutButton->addWidget(pause_button);
    layoutButton->addStretch(1);

    layoutSaveNload->addStretch(1);
    layoutSaveNload->addWidget(save_button);
    layoutSaveNload->addWidget(load_button);
    layoutSaveNload->addWidget(clearAllFiles_button);
    layoutSaveNload->addWidget(addHealthpack_button);
    layoutSaveNload->addStretch(1);

    //add all widget to overall layout
    layoutStatistic->addWidget(xpositionGroup);
    layoutStatistic->addWidget(ypositionGroup);
    layoutStatistic->addWidget(dxdyGroup);
    layoutStatistic->addWidget(aStarNProtaGroup);
    layoutStatistic->addWidget(healthGroup);
    layoutStatistic->addWidget(energyGroup);
    layoutStatistic->addLayout(layoutButton);
    layoutStatistic->addLayout(layoutSaveNload);


    // connect button
    connect(protaSpeed,SIGNAL(editingFinished()),this,SLOT(handleSpeed()));
    connect(switch_button, SIGNAL (released()), this, SLOT (handleSwitchButton()));
    connect(start_game_button, SIGNAL (released()), this, SLOT (handleStartButton()));
    connect(chooseNewMap, SIGNAL (released()), this, SLOT (handleMapButton()));
    connect(auto_button,SIGNAL (released()), this, SLOT (autoNavigate()));
    connect(pause_button,SIGNAL (released()), this, SLOT (handlePauseButton()));
    connect(save_button,SIGNAL (released()), this, SLOT (handleSaveButton()));
    connect(load_button,SIGNAL (released()), this, SLOT (handleLoadButton()));
    connect(addHealthpack_button,SIGNAL (released()), this, SLOT (handleAddHealthpackButton()));
    connect(clearAllFiles_button,SIGNAL (released()), this, SLOT (handleClearAllFilesButton()));


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
    connect(terminalGameView,&TerminalGameView::destinationFind,graphicGameView,&GraphicGameView::drawThePath);
    connect(myModel->getMyProtagonist(), SIGNAL (findNext()), this, SLOT (autoNavigate()));
    connect(terminalGameView,&TerminalGameView::wChanged,this,&MainWindow::showWChanged);
    connect(terminalGameView,&TerminalGameView::automaticRun,this,&MainWindow::autoNavigate);

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

void MainWindow::setCurrentFileName(const QString &valuehandleSaveButton)
{
    currentFileName = valuehandleSaveButton;
}

void MainWindow::removeEveryFromTheScene()
{
    for(auto &aTile:myModel->getMyTilesMap()){
        graphicGameView->scene->removeItem(aTile);
    }
    //add pack to the scene and connect
    for(auto &aPack:myModel->getMyHealthPacks()){
        graphicGameView->scene->removeItem(aPack);
    }
    // add the Enemies to the scene
    for(auto &aEnemy:myModel->getMyEnemies()){
        graphicGameView->scene->removeItem(aEnemy);
    }

    //add pEnemies to the scene and connect
    for(auto &aPEnemy:myModel->getMyPEnemies()){
        graphicGameView->scene->removeItem(aPEnemy);
    }
    graphicGameView->scene->removeItem(myModel->getMyProtagonist());
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

void MainWindow::restartTheGame()
{
    int result = QMessageBox::warning(this, tr("My Game"),
                                      tr("You Are Dead.\n Do you want to play agin?"),
                                      QMessageBox::Yes | QMessageBox::No);
    switch (result) {
    case QMessageBox::Yes:
        hide();
        QMessageBox::information(this,"Loading","Restarting the game... please wait a bit...",true);
        delete myModel->getMyProtagonist();
        delete myModel;
        delete terminalGameView;
        delete graphicGameView;
        myModel = new MyModel(currentFileName);
        gameSetting();
        myModel->modelInitialize();
        terminalGameView = new TerminalGameView();
        graphicGameView = new GraphicGameView();
        graphicGameView->initialGraphicView();
        reset();
        show();
        break;
    case QMessageBox::No:
        close();
        break;
    default:
        break;
    }
}

void MainWindow::showWChanged()
{
    aStarParameter->setText(QString::number(myModel->getW()));
}


void MainWindow::handleSwitchButton()
{
    myModel->setWhichView(!myModel->getWhichView());
    bool whichView = myModel->getWhichView();
    if(whichView){
        terminalGameView->show();
        graphicGameView->hide();
        aStarParameter->setReadOnly(true);
    }
    else{
        terminalGameView->hide();
        graphicGameView->show();
        aStarParameter->setReadOnly(false);
    }
}

void MainWindow::handleStartButton()
{
    //Model get the destination x and y , false is graphicView , true is terinalView
    bool whichView = myModel->getWhichView();
    if(whichView){
        //        myModel->setDestinationX(22);
        //        myModel->setDestinationY(22);
    }
    else{
        myModel->setDestinationX(round((destinationX->text()).toDouble()));
        myModel->setDestinationY(round((destinationY->text()).toDouble()));
    }

    if(myModel->moveFast()){
        myModel->setOnceOrMore(true);
        //emit pathFound(round((protaSpeed->text()).toInt()));
        emit pathFound(myModel->getSpeed());

    }else{
        //        qDebug()<<"Can not find the path";
        QMessageBox::information(this,"Error","The given destination is unreachable!",true);
    }
}


void MainWindow::handleMapButton()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,
                                            tr("Open Image"), "/home", tr("Image Files (*.png *.jpg *.bmp)"));
    qDebug()<<fileName;
    if(fileName != NULL)
    {
        hide();
        QMessageBox::information(this,"Loading","Creating the new world... please wait a bit...",true);
        delete myModel;
        delete terminalGameView;
        delete graphicGameView;
        setCurrentFileName(fileName);
        myModel = new MyModel(fileName);
        gameSetting();
        myModel->modelInitialize();
        terminalGameView = new TerminalGameView();
        graphicGameView = new GraphicGameView();
        graphicGameView->initialGraphicView();
        reset();
        show();
        QMessageBox::information(this,"Success","Congratulations! New map is ready to use! :)",true);
    }        qDebug()<<"w is: "<<myModel->getW();

}

void MainWindow::autoNavigate()
{
    if(myModel->getWhichView()){
        //terminal use command to change W.
        qDebug()<<"auto terminal";
    }
    else{
        myModel->setW((aStarParameter->text()).toFloat());
        qDebug()<<"autonavigaet";
    }
    bool moreEnemy = myModel->FindNextStep();
    if (moreEnemy)
    {
        myModel->setOnceOrMore(false);
        emit pathFound(myModel->getSpeed());
    }
    else
    {
        int result = QMessageBox::information(this, tr("My Game"),
                                              tr("Congratulations! You win!\n Do you want to play agin?"),
                                              QMessageBox::Yes | QMessageBox::No);
        switch (result) {
        case QMessageBox::Yes:
            hide();
            QMessageBox::information(this,"Loading","Creating the new world... please wait a bit... :)",true);
            delete myModel;
            delete terminalGameView;
            delete graphicGameView;
            myModel = new MyModel(currentFileName);
            gameSetting();
            myModel->modelInitialize();
            terminalGameView = new TerminalGameView();
            graphicGameView = new GraphicGameView();
            graphicGameView->initialGraphicView();
            reset();
            show();
            break;
        case QMessageBox::No:
            close();
            break;
        default:
            break;
        }
    }

}

void MainWindow::handlePauseButton()
{
    myModel->getMyProtagonist()->setPaused(!myModel->getMyProtagonist()->getPaused());
}

void MainWindow::handleSaveButton()
{

    bool ok;
    QString text = QInputDialog::getText(this, tr("Save"),
                                         tr("Name:"), QLineEdit::Normal,
                                         NULL, &ok);
    if (ok && !text.isEmpty())
    {
        /*by default stored in home./config/Team104/filename*/
        QMessageBox::information(this,"Saving","The game is saving... please wait a bit...",true);
        myModel->saveGame(text);
        saveFileNames.push_back(text);
        QMessageBox::information(this,"Success","Save successfully!",true);
    }
    else if ((ok && text.isEmpty()))
    {
        QMessageBox::information(this,"Error","The record name cannot be empty!",true);
    }

}

void MainWindow::handleLoadButton()
{
    QFileInfo check_file("./save_filenames.txt");
    if (check_file.exists() && check_file.isFile())
    {
        QStringList fileNameList;

        /*read filenames from local file*/
        QFile file("save_filenames.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            fileNameList<<line;
        }

        CustomDialog dialog(fileNameList);
        if (dialog.exec() == QDialog::Accepted)
        {
            QString fileName = dialog.comboBox()->currentText();

            if (fileName != NULL)
            {
                hide();
                QMessageBox::information(this,"Loading","Game is loading... please wait a bit :)",true);
                //    delete terminalGameView;
                removeEveryFromTheScene();
                myModel->loadGame(fileName);
                //    terminalGameView = new TerminalGameView();
                graphicGameView->initialGraphicView();   //terminal initial may be needed
                show();
                QMessageBox::information(this,"Success","Load successfully! Welcome back!",true);
            }
            else show();
        }

    }
    else
    {
        QMessageBox::information(this,"Error","Sorry.. there is no record yet",true);
    }




}

void MainWindow::handleAddHealthpackButton()
{
    qsrand(QDateTime::currentMSecsSinceEpoch());
    int x = myModel->getMyProtagonist()->getXPos();
    int y = myModel->getMyProtagonist()->getYPos();
    float value = qrand()%100;
    HealthPack *aHealthpack = new HealthPack(x+1,y,value);
    myModel->getMyHealthPacks().push_back(aHealthpack);
    graphicGameView->scene->addItem(aHealthpack);
}

void MainWindow::handleClearAllFilesButton()
{
    if(QDir(QDir::homePath()+"/.config/Team104").entryInfoList(QDir::NoDotAndDotDot|QDir::AllEntries).count() != 0)
    {
        QFile file("save_filenames.txt");
        file.remove();
        myModel->clearAllSaves();
        QMessageBox::information(this,"Success","The record files are deleted!",true);
    }
    else
    {
        QMessageBox::information(this,"Warning","There are no record files!",true);
    }
}

void MainWindow::handleSpeed()
{
    myModel->setSpeed(round((protaSpeed->text()).toDouble()));
    emit speedChanged(round((protaSpeed->text()).toDouble()));
    qDebug()<<"model is "<<myModel->getSpeed();
}




