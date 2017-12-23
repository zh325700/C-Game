#include<QDebug>
#include "ui_mainwindow.h"
#include "world.h"
#include <QDebug>
#include "TerminalGameView.h"
#include "MyModel.h"

using namespace std;

extern MyModel *myModel;
TerminalGameView::TerminalGameView(QWidget *parent) :
    QWidget(parent)
{
    setupLayout();
    init();
    initWorld();

    output->appendPlainText(">>The game is starting! \n"
                            "  From now on, you can use command lines to do the following things: \n"
                            "  get information of protagonist with: 'show prota' \n"
                            "  show near enemies with: 'show enemies' \n"
                            "  show all enemies with: 'show all enemies' \n"
                            "  show near health packs with: 'show health packs' \n"
                            "  show all health packswith: 'show all health packs' \n"
                            "  use 'arrows'a,w,s,d' in the keyboard to control the movement \n"
                            "  you can enter 'help' to get manual at any time");

    connect(lineEdit,&QLineEdit::returnPressed,this,&TerminalGameView::onEnter);
    connect(myProtagonist,&MyProtagonist::posChanged,this,&TerminalGameView::checkNewPos);
    connect(myProtagonist,&MyProtagonist::encounterPenemy,this,&TerminalGameView::encounterPEn);
    connect(myProtagonist,&MyProtagonist::encounterEnemy,this,&TerminalGameView::encouterEn);
    connect(myProtagonist,&MyProtagonist::encounterHealthPack,this,&TerminalGameView::encouterHe);

    for(auto& ene:myEnemies){
            QObject::connect(ene,&MyEnemy::dead,this,&TerminalGameView::enemyDead);
    }

    for(auto& pene:myPEnemies){
                connect(pene,&MyPEnemy::poisonLevelUpdated,this,&TerminalGameView::poisonUser);
                connect(pene,&MyPEnemy::dead,this,&TerminalGameView::penemyDead);
            }
}

TerminalGameView::~TerminalGameView(){}

void TerminalGameView::init()
{
    helpText = "You can use command lines to do the following things:\n "
               "  'show prota' get information of protagonist\n"
               "  'show enemies' find near enemies in this map \n"
               "  'show all enemies' find all enemies in this map \n"
               "  'show health packs' find near health packs \n"
               "  'show all health packs' find all health packs \n"
               "  use 'a,w,s,d' in the keyboard to control the movement \n"
               "  you can enter 'help' to get manual at any time";
    boundary = "You are moving out of boundary\n";
    existwall = "There is wall blocking your way, you cannot move in this direction\n";
}

void TerminalGameView::initWorld()
{
    myTilesMap = myModel->myTilesMap;
    myEnemies = myModel->myEnemies;
    myPEnemies = myModel->myPEnemies;
    myHealthPacks = myModel->myHealthPacks;
    myProtagonist = myModel->myProtagonist;
    rows = myModel->rows;
    cols = myModel->cols;

}

void TerminalGameView::setupLayout(){

    auto groupOutput  = new QGroupBox();
    auto groupOutLayout = new QVBoxLayout(groupOutput);
    auto plabel = new QLabel("output: ");
    output = new QPlainTextEdit();
    output->setFont(font);
    output->setCenterOnScroll(true);
    output->setReadOnly(true);
    output->resize(800,600);
    output->setGeometry(0,0,800,600);
    groupOutLayout->addWidget(plabel);
    groupOutLayout->addWidget(output);
    output->setStyleSheet("QPlainTextEdit{color: #ffff00; background-color: #303030;"
                              " selection-background-color: #606060; selection-color: #ffffff;}");

    auto group = new QGroupBox();
    auto groupLayout = new QHBoxLayout(group);
    auto label = new QLabel("input: ");
    lineEdit = new QLineEdit();
    groupLayout->addWidget(label);
    groupLayout->addWidget(lineEdit);

    auto mainLayout = new QGridLayout(this);
    mainLayout->addWidget(groupOutput);
    mainLayout->addWidget(group);
}

void TerminalGameView::moveEnemy()
{
    for(auto &enemy : myEnemies){
        QString strength = QString::number(enemy->getValue());
        if((enemy->getXPos() == myProtagonist->getXPos()-1)&&(enemy->getYPos() == myProtagonist->getYPos())){
            output->appendPlainText("  Warning: there is a normal enemy on your left, whose strength is "+strength);
        }
        if((enemy->getXPos() == myProtagonist->getXPos()+1)&&(enemy->getYPos() == myProtagonist->getYPos())){
            output->appendPlainText("  Warning: there is a normal enemy on your right, whose strength is "+strength);
        }
        if((enemy->getXPos() == myProtagonist->getXPos())&&(enemy->getYPos() == myProtagonist->getYPos()-1)){
            output->appendPlainText("  Warning: there is a normal enemy above you, whose strength is "+strength);
        }
        if((enemy->getXPos() == myProtagonist->getXPos())&&(enemy->getYPos() == myProtagonist->getYPos()+1)){
            output->appendPlainText("  Warning: there is a normal enemy below you, whose strength is "+strength);
        }
    }

    for(auto &enemy : myPEnemies){
        QString strength = QString::number(enemy->getValue());
        if((enemy->getXPos() == myProtagonist->getXPos()-1)&&(enemy->getYPos() == myProtagonist->getYPos())){
            output->appendPlainText("  Warning: there is a poison enemy on your left, whose strength is "+strength);
        }
        if((enemy->getXPos() == myProtagonist->getXPos()+1)&&(enemy->getYPos() == myProtagonist->getYPos())){
            output->appendPlainText("  Warning: there is a poison enemy on your right, whose strength is "+strength);
        }
        if((enemy->getXPos() == myProtagonist->getXPos())&&(enemy->getYPos() == myProtagonist->getYPos()-1)){
            output->appendPlainText("  Warning: there is a poison enemy above you, whose strength is "+strength);
        }
        if((enemy->getXPos() == myProtagonist->getXPos())&&(enemy->getYPos() == myProtagonist->getYPos()+1)){
            output->appendPlainText("  Warning: there is a poison enemy below you, whose strength is "+strength);
        }
    }
}

bool TerminalGameView::movePos(QString direction)
{
    bool pos = false;

    if(direction == "left"){
        if((myProtagonist->getXPos() - 1)>=0){
            pos = true;
        }
    }
    else if(direction=="right"){
        if((cols-1) >= (myProtagonist->getXPos() + 1)){
            pos = true;
        }
    }
    else if(direction=="up"){
        if((myProtagonist->getYPos() - 1) >= 0){
            pos = true;
        }
    }
    else if(direction=="down"){
        if((rows-1) >= (myProtagonist->getYPos() + 1)){
            pos = true;
        }
    }

    return pos;
}

bool TerminalGameView::movenoWall(QString direction)
{
    bool noWall = true;

    if(direction=="left"){
        if(movePos(direction)){
            if(isinf(myTilesMap.at(myProtagonist->getYPos()*cols+myProtagonist->getXPos()-1)->getValue())){
                noWall = false;
            }
        }
    }

    else if(direction=="right"){
        if(movePos(direction)){
            if(isinf(myTilesMap.at(myProtagonist->getYPos()*cols+myProtagonist->getXPos()+1)->getValue())){
                    noWall = false;
            }
        }
    }

    else if(direction=="up"){
        if(movePos(direction)){
            if(isinf(myTilesMap.at((myProtagonist->getYPos()-1)*cols+myProtagonist->getXPos())->getValue())){
                noWall = false;
            }
        }
    }

    else if(direction=="down"){
        if(movePos(direction)){
            if(isinf(myTilesMap.at((myProtagonist->getYPos()+1)*cols+myProtagonist->getXPos())->getValue())){
                noWall = false;
            }
        }
    }

    return noWall;
}

void TerminalGameView::findAllEnemy()
{
    for(auto &enemy : myEnemies){

        QString xPosition = QString::number(enemy->getXPos());
        QString yPosition = QString::number(enemy->getYPos());
        QString strength = QString::number(enemy->getValue());

        output->appendPlainText("  A normal enemy is at the location ("+xPosition+","+yPosition
                                   +"), his strength is "+strength);
    }

    for(auto &penemy :myPEnemies){
        QString xPosition = QString::number(penemy->getXPos());
        QString yPosition = QString::number(penemy->getYPos());
        QString strength = QString::number(penemy->getValue());

        output->appendPlainText("  A poison enemy is at the location ("+xPosition+","+yPosition
                                   +"), his strength is "+strength);
    }
}

void TerminalGameView::findNearEnemy()
{
    for(auto &enemy : myEnemies){

        QString xPosition = QString::number(enemy->getXPos());
        QString yPosition = QString::number(enemy->getYPos());
        QString strength = QString::number(enemy->getValue());

        if((abs(enemy->getXPos()-myProtagonist->getXPos())<=10)&&(abs(enemy->getYPos()-myProtagonist->getYPos())<=10)){
            output->appendPlainText("  A normal enemy is at the location ("+xPosition+","+yPosition
                                   +"), his strength is "+strength);
        }
    }

    for(auto &penemy :myPEnemies){
        QString xPosition = QString::number(penemy->getXPos());
        QString yPosition = QString::number(penemy->getYPos());
        QString strength = QString::number(penemy->getValue());

        if((abs(penemy->getXPos()-myProtagonist->getXPos())<=10)&&(abs(penemy->getYPos()-myProtagonist->getYPos())<=10)){
            output->appendPlainText("  A poison enemy is at the location ("+xPosition+","+yPosition
                                   +"), his strength is "+strength);
        }
    }
}

void TerminalGameView::findAllHealth()
{
    for(auto &healthP : myHealthPacks){

        QString xPosition = QString::number(healthP->getXPos());
        QString yPosition = QString::number(healthP->getYPos());
        QString strength = QString::number(healthP->getValue());

        output->appendPlainText("  A health pack is at the location ("+xPosition+","+yPosition+"), it is value is "+strength);
    }
}

void TerminalGameView::findNearHealth()
{
    for(auto &healthP : myHealthPacks){

        QString xPosition = QString::number(healthP->getXPos());
        QString yPosition = QString::number(healthP->getYPos());
        QString strength = QString::number(healthP->getValue());

        if((abs(healthP->getXPos()-myProtagonist->getXPos())<=10)&&(abs(healthP->getYPos()-myProtagonist->getYPos())<=10)){
            output->appendPlainText("  A health pack is at the location ("+xPosition+","+yPosition+"), the value is "+strength);
        }
    }
}

QString TerminalGameView::showProta()
{
    QString protaInfo = "protagonist is at ("
                    +QString::number(myProtagonist->getXPos())+","+QString::number(myProtagonist->getYPos())
                    +"), health is "+QString::number(myProtagonist->getHealth())
                    +", energy is "+QString::number(myProtagonist->getEnergy());

    return protaInfo;
}

void TerminalGameView::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_A){
        QString direction = "left";
        bool movable = ((movePos(direction))&&(movenoWall(direction)));

        if(movable){
            myProtagonist->Protagonist::setXPos((myProtagonist->getXPos()-1));
        }

        else{
            QString unmove="";
            if(!movePos(direction)){
                unmove = unmove+boundary;
            }
            if(!movenoWall(direction)){
                unmove = unmove+existwall;
            }

            output->appendPlainText(">>"+unmove);
        }
    }

    else if(event->key() == Qt::Key_D){
        QString direction = "right";
        bool movable = ((movePos(direction))&&(movenoWall(direction)));

        if(movable){
            myProtagonist->Protagonist::setXPos((myProtagonist->getXPos()+1));
        }

        else{
            QString unmove="";
            if(!movePos(direction)){
                unmove = unmove+boundary;
            }
            if(!movenoWall(direction)){
                unmove = unmove+existwall;
            }

            output->appendPlainText(">>"+unmove);
    }
 }

    else if(event->key() == Qt::Key_W){
        QString direction = "up";
        bool movable = ((movePos(direction))&&(movenoWall(direction)));

        if(movable){
            myProtagonist->Protagonist::setYPos(myProtagonist->getYPos()-1);
        }

        else{
            QString unmove="";
            if(!movePos(direction)){
                unmove = unmove+boundary;
            }
            if(!movenoWall(direction)){
                unmove = unmove+existwall;
            }

            output->appendPlainText(">>"+unmove);
        }
    }

    else if(event->key() == Qt::Key_S){
        QString direction = "down";
        bool movable = ((movePos(direction))&&(movenoWall(direction)));

        if(movable){
            myProtagonist->Protagonist::setYPos(myProtagonist->getYPos()+1);
        }

        else{
            QString unmove="";
            if(!movePos(direction)){
                unmove = unmove+boundary;
            }
            if(!movenoWall(direction)){
                unmove = unmove+existwall;
            }

            output->appendPlainText(">>"+unmove);
        }
    }
    else if(event->key() == Qt::Key_Up){
        if(inputPosition > 0){
        lineEdit->setText(inputs.at(inputPosition-1));
        inputPosition = inputPosition-1;
        }
        else{
            lineEdit->setText(inputs.at(inputs.size()-1));
            inputPosition = inputs.size()-1;
        }
    }

    else if(event->key() == Qt::Key_Down){
        if(inputPosition < inputs.size()-1){
        lineEdit->setText(inputs.at(inputPosition+1));
        inputPosition = inputPosition+1;
        }
        else{
            lineEdit->setText(inputs.at(0));
            inputPosition = 0;
        }
    }
}

void TerminalGameView::onEnter()
{
    QString input = lineEdit->text();
    output->appendPlainText(">>"+input);
    inputs.push_back(input);
    inputPosition = inputs.size()-1;

    if(input=="help"){
        output->appendPlainText(">>" + helpText);
        lineEdit->clear();
    }

    else if(input=="show prota"){

        output->appendPlainText(">>" + showProta());
        lineEdit->clear();
    }

    else if(input=="show enemies"){
        output->appendPlainText(">>the locations of near enemies are following:");
        findNearEnemy();
        lineEdit->clear();
    }

    else if(input=="show all enemies"){
        output->appendPlainText(">>the locations of all enemies are following:");
        findAllEnemy();
        lineEdit->clear();
    }

    else if(input == "show health packs"){
        output->appendPlainText(">>the locations of near health packs are following: ");
        findNearHealth();
        lineEdit->clear();
    }

    else if(input == "show all health packs"){
        output->appendPlainText(">>the locations of near health packs are following:");
        findAllHealth();
        lineEdit->clear();
    }

    else{
        output->appendPlainText(">>invalid command, please enter 'help' to get more information");
        lineEdit->clear();
    }
}

void TerminalGameView::encouterEn()
{
    output->appendPlainText("  Ah!");
}

void TerminalGameView::encounterPEn()
{
    output->appendPlainText("  You meet one poison enemy, it will poison you, run as quick as possible!");
}

void TerminalGameView::encouterHe()
{
    output->appendPlainText("  Congratulations! You get a health pack and your health is "+QString::number(myProtagonist->getHealth())+" now");
}

void TerminalGameView::enemyDead()
{
    qDebug()<<"xuqingjie enemydead";  //just print
    output->appendPlainText("  Congratulations! You has defeated one enemy and your energy is full now!");
}

void TerminalGameView::penemyDead()
{
    output->appendPlainText("  Congratulations! You has defeated one poison enemy and your energy is full now!");
}

void TerminalGameView::poisonUser()
{
    output->appendPlainText("  You are being poiosned, your health is "+QString::number(myProtagonist->getHealth())+" now");
}

void TerminalGameView::checkNewPos()
{
    output->appendPlainText(">>"+showProta());

    moveEnemy();

}



