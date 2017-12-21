
#include<QDebug>
#include "ui_mainwindow.h"
#include "world.h"
#include <QDebug>
#include "GameTerminal.h"
#include "MyModel.h"

using namespace std;

extern MyModel *myModel;
GameTerminal::GameTerminal(QWidget *parent) :
    QWidget(parent)
{
    setupLayout();
    init();
    initWorld();

    output->appendPlainText(">>The game is starting! \n"
                             "    From now on, you can use command lines to do the following things: \n"
                             "    get information of protagonist with: 'show prota' \n"
                             "    find all enemies with: 'find enemy' \n"
                             "    find all health packswith: 'find health packs' \n"
                             "    defeat enemy with: 'defeat(xposition,yposition)' \n"
                             "    use 'arrows'a,w,s,d' in the keyboard to control the movement \n"
                             "    you can choose the speed with 'speed(1)' \n"
                             "    you can enter 'help' to get manual at any time");

    connect(lineEdit,&QLineEdit::returnPressed,this,&GameTerminal::onEnter);
    connect(user,&MyProtagonist::posChanged,this,&GameTerminal::checkNewPos);
    connect(user,&MyProtagonist::healthChanged,this,&GameTerminal::checkHealth);
    connect(user,&MyProtagonist::energyChanged,this,&GameTerminal::checkEnergy);

    for(auto& ene:myEnemies){
           // connect(ene,&MyEnemy::dead,this,&GameTerminal::enemyDead);
            QObject::connect(ene,&MyEnemy::dead,this,&GameTerminal::enemyDead);
    }

    for(auto& pene:myPEnemies){
//        connect(this,&GameTerminal::penemyDefeating,pene,&MyPEnemy::poison);
//        connect(pene,&MyPEnemy::poisonLevelUpdated,this,&GameTerminal::poisonUser);
//        connect(pene,&MyPEnemy::dead,this,&GameTerminal::penemyDead);
    }

}

GameTerminal::~GameTerminal(){}

void GameTerminal::init()
{
    helpText = "You can use command lines to do the following things: \n "
               "'show prota' get information of protagonist with \n"
               "'show enemies' find near enemies in this map \n"
               "'show all enemies' find all enemies in this map \n"
               "'show health packs' find near health packs \n"
               "'show all health packs' find all health packs \n"
               "use 'a,w,s,d' in the keyboard to control the movement \n"
               "you can enter 'help' to get manual at any time";

        boundary = "You are moving out of boundary\n";
        existwall = "There is wall blocking your way, you cannot move in this direction\n";
        existEnemy = "There are enemies in the way, you cannot move\n";
}

void GameTerminal::initWorld()
{
    aw = myModel->myTilesMap;
    myEnemies = myModel->myEnemies;
    myPEnemies = myModel->myPEnemies;
    myHealthPacks = myModel->myHealthPacks;
    user = myModel->myProtagonist;
    row = myModel->rows;
    col = myModel->cols;

}

void GameTerminal::setupLayout(){

    auto groupOutput  = new QGroupBox();
    auto groupOutLayout = new QVBoxLayout(groupOutput);
    auto plabel = new QLabel("output: ");
    output = new QPlainTextEdit();
    output->setCenterOnScroll(true);
    output->setReadOnly(true);
    output->resize(500,500);
    output->setGeometry(0,0,500,500);
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

bool GameTerminal::addHealth(int x, int y)
{
    bool isHealth = false;

    for (std::vector< HealthPack* >::iterator healthPack = myHealthPacks.begin() ; healthPack != myHealthPacks.end(); ++healthPack){
        if(((*healthPack)->getXPos() == x)&&((*healthPack)->getYPos() == y)){
            if(user->getHealth()+(*healthPack)->getValue() >= 100){
                user->setHealth(100.00f);
            }
            else{
                user->setHealth(user->getHealth()+(*healthPack)->getValue());
            }
            isHealth = true;
            delete (*healthPack);
        }
    }

    return isHealth;
}

bool GameTerminal::movePos(QString direction)
{
    bool pos = false;

    if(direction == "left"){
        if((user->getXPos() - 1)>=0){
            pos = true;
        }
    }
    else if(direction=="right"){
        if((col-1) >= (user->getXPos() + 1)){
            pos = true;
        }
    }
    else if(direction=="up"){
        if((user->getYPos() - 1) >= 0){
            pos = true;
        }
    }
    else if(direction=="down"){
        if((row-1) >= (user->getYPos() + 1)){
            pos = true;
        }
    }

    return pos;
}

bool GameTerminal::movenoWall(QString direction)
{
    bool noWall = true;

    if(direction=="left"){
        if(movePos(direction)){
            if(isinf(aw.at(user->getYPos()*col+user->getXPos()-1)->getValue())){
                noWall = false;
            }
        }
    }

    else if(direction=="right"){
        if(movePos(direction)){
            if(isinf(aw.at(user->getYPos()*col+user->getXPos()+1)->getValue())){
                    noWall = false;
            }
        }
    }

    else if(direction=="up"){
        if(movePos(direction)){
            if(isinf(aw.at((user->getYPos()-1)*col+user->getXPos())->getValue())){
                noWall = false;
            }
        }
    }

    else if(direction=="down"){
        if(movePos(direction)){
            if(isinf(aw.at((user->getYPos()+1)*col+user->getXPos())->getValue())){
                noWall = false;
            }
        }
    }

    return noWall;
}

void GameTerminal::moveEnemy()
{
    for(auto &enemy : myEnemies){
        QString strength = QString::number(enemy->getValue());
        if((enemy->getXPos() == user->getXPos()-1)&&(enemy->getYPos() == user->getYPos())){
            output->appendPlainText("   Warning: there is a normal enemy on your left, whose strength is "+strength);
        }
        if((enemy->getXPos() == user->getXPos()+1)&&(enemy->getYPos() == user->getYPos())){
            output->appendPlainText("   Warning: there is a normal enemy on your right, whose strength is "+strength);
        }
        if((enemy->getXPos() == user->getXPos())&&(enemy->getYPos() == user->getYPos()-1)){
            output->appendPlainText("   Warning: there is a normal enemy above you, whose strength is "+strength);
        }
        if((enemy->getXPos() == user->getXPos())&&(enemy->getYPos() == user->getYPos()+1)){
            output->appendPlainText("   Warning: there is a normal enemy below you, whose strength is "+strength);
        }
    }

    for(auto &enemy : myPEnemies){
        QString strength = QString::number(enemy->getValue());
        if((enemy->getXPos() == user->getXPos()-1)&&(enemy->getYPos() == user->getYPos())){
            output->appendPlainText("   Warning: there is a poison enemy on your left, whose strength is "+strength);
        }
        if((enemy->getXPos() == user->getXPos()+1)&&(enemy->getYPos() == user->getYPos())){
            output->appendPlainText("   Warning: there is a poison enemy on your right, whose strength is "+strength);
        }
        if((enemy->getXPos() == user->getXPos())&&(enemy->getYPos() == user->getYPos()-1)){
            output->appendPlainText("   Warning: there is a poison enemy above you, whose strength is "+strength);
        }
        if((enemy->getXPos() == user->getXPos())&&(enemy->getYPos() == user->getYPos()+1)){
            output->appendPlainText("   Warning: there is a poison enemy below you, whose strength is "+strength);
        }
    }
}

float GameTerminal::totalEnergy(QString direction)
{
    float sum = 0;

    if(direction=="left"){
        if(movePos(direction)){
            sum = abs(aw.at(user->getYPos()*col+user->getXPos()-1)->getValue()-aw.at(user->getYPos()*col+user->getXPos())->getValue());
        }
    }
    else if(direction=="right"){
        if(movePos(direction)){
            sum = abs(aw.at(user->getYPos()*col+user->getXPos()+1)->getValue()-aw.at(user->getYPos()*col+user->getXPos())->getValue());
        }
    }

    else if(direction=="up"){
        if(movePos(direction)){
            sum = abs(aw.at((user->getYPos()-1)*col+user->getXPos())->getValue()-aw.at((user->getYPos())*col+user->getXPos())->getValue());
        }
    }

    else if(direction=="down"){
        if(movePos(direction)){
            sum = abs(aw.at((user->getYPos()+1)*col+user->getXPos())->getValue()-aw.at((user->getYPos())*col+user->getXPos())->getValue());
        }
    }

    if(sum == std::numeric_limits<float>::infinity()){
        sum = 0;
    }

    sum = sum + costOfStep;

    return sum;
}

bool GameTerminal::moveEnergy(QString direction)
{
    bool gEnergy = true;

    if(totalEnergy(direction) > user->getEnergy()){
        gEnergy = false;

    }

    return gEnergy;
}

void GameTerminal::findAllEnemy()
{
    for(auto &enemy : myEnemies){

        QString xPosition = QString::number(enemy->getXPos());
        QString yPosition = QString::number(enemy->getYPos());
        QString strength = QString::number(enemy->getValue());

        output->appendPlainText("A normal enemy is at the location ("+xPosition+","+yPosition
                                   +"), his strength is "+strength);
    }

    for(auto &penemy :myPEnemies){
        QString xPosition = QString::number(penemy->getXPos());
        QString yPosition = QString::number(penemy->getYPos());
        QString strength = QString::number(penemy->getValue());

        output->appendPlainText("A poison enemy is at the location ("+xPosition+","+yPosition
                                   +"), his strength is "+strength);
    }
}

void GameTerminal::findNearEnemy()
{
    for(auto &enemy : myEnemies){

        QString xPosition = QString::number(enemy->getXPos());
        QString yPosition = QString::number(enemy->getYPos());
        QString strength = QString::number(enemy->getValue());

        if((abs(enemy->getXPos()-user->getXPos())<=10)&&(abs(enemy->getYPos()-user->getYPos())<=10)){
            output->appendPlainText("A normal enemy is at the location ("+xPosition+","+yPosition
                                   +"), his strength is "+strength);
        }
    }

    for(auto &penemy :myPEnemies){
        QString xPosition = QString::number(penemy->getXPos());
        QString yPosition = QString::number(penemy->getYPos());
        QString strength = QString::number(penemy->getValue());

        if((abs(penemy->getXPos()-user->getXPos())<=10)&&(abs(penemy->getYPos()-user->getYPos())<=10)){
            output->appendPlainText("A poison enemy is at the location ("+xPosition+","+yPosition
                                   +"), his strength is "+strength);
        }
    }
}

void GameTerminal::findAllHealth()
{
    for(auto &healthP : myHealthPacks){

        QString xPosition = QString::number(healthP->getXPos());
        QString yPosition = QString::number(healthP->getYPos());
        QString strength = QString::number(healthP->getValue());

        output->appendPlainText("A health pack is at the location ("+xPosition+","+yPosition+"), it is value is "+strength);
    }
}

void GameTerminal::findNearHealth()
{
    for(auto &healthP : myHealthPacks){

        QString xPosition = QString::number(healthP->getXPos());
        QString yPosition = QString::number(healthP->getYPos());
        QString strength = QString::number(healthP->getValue());

        if((abs(healthP->getXPos()-user->getXPos())<=10)&&(abs(healthP->getYPos()-user->getYPos())<=10)){
            output->appendPlainText("A health pack is at the location ("+xPosition+","+yPosition+"), the value is "+strength);
        }
    }
}

QString GameTerminal::showProta()
{
    QString protaInfo = "protagonist is at ("
                    +QString::number(user->getXPos())+","+QString::number(user->getYPos())
                    +"), health is "+QString::number(user->getHealth())
                    +", energy is "+QString::number(user->getEnergy());

    return protaInfo;
}

void GameTerminal::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_A){
        QString direction = "left";
        bool movable = ((movePos(direction))&&(movenoWall(direction)));

        if(movable){
            if(moveEnergy(direction)){
                user->setEnergy(user->getEnergy()-totalEnergy(direction));
                user->Protagonist::setXPos((user->getXPos()-1));
                }
            else{
                user->setEnergy(0.0f);
                user->Protagonist::setXPos((user->getXPos()-1));

            }
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
            if(moveEnergy(direction)){
                user->setEnergy(user->getEnergy()-totalEnergy(direction));
                user->Protagonist::setXPos((user->getXPos()+1));
            }
            else{
                user->setEnergy(0.0f);
                user->Protagonist::setXPos((user->getXPos()+1));
            }
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
            if(moveEnergy(direction)){
                user->setEnergy(user->getEnergy()-totalEnergy(direction));
                user->Protagonist::setYPos(user->getYPos()-1);
                }
            else{
                user->setEnergy(0.0f);
                user->Protagonist::setYPos(user->getYPos()-1);
            }
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
            if(moveEnergy(direction)){
                user->setEnergy(user->getEnergy()-totalEnergy(direction));
                user->Protagonist::setYPos(user->getYPos()+1);
            }
            else{
                user->setEnergy(0.0f);
                user->Protagonist::setYPos(user->getYPos()+1);
            }
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

void GameTerminal::onEnter()
{
    QString input = lineEdit->text();
    output->appendPlainText(">> "+input);
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
        output->appendPlainText(">> the locations of near enemies are following:");
        findNearEnemy();
        lineEdit->clear();
    }

    else if(input=="show all enemies"){
        output->appendPlainText(">> the locations of all enemies are following:");
        findAllEnemy();
        lineEdit->clear();
    }

    else if(input == "show health packs"){
        output->appendPlainText(">>the locations of near health packs are following: ");
        findNearHealth();
        lineEdit->clear();
    }

    else if(input == "show all health packs"){
        output->appendPlainText(">> there are " +QString::number(myHealthPacks.size())+" health packs in this world now");
        findAllHealth();
        lineEdit->clear();
    }

    else{
        output->appendPlainText(">> invalid command, please enter 'help' to get more information");
        lineEdit->clear();
    }
}

void GameTerminal::enemyDead()
{
    qDebug()<<"xuqingjie enemydead";
    output->appendPlainText(">> Congratulations! You has defeated one enemy and your energy is full now!");
    MyEnemy *obj = (MyEnemy *)sender();
    delete obj;
//    for (std::vector< MyEnemy* >::iterator eneDead = myEnemies.begin() ; eneDead != myEnemies.end(); ++eneDead){
//        if(((*eneDead)->getXPos() == obj->getXPos())&&((*eneDead)->getYPos()==obj->getYPos())){
//            delete (*eneDead);
//        }
//    }
}

void GameTerminal::penemyDead()
{
    output->appendPlainText(">> Congratulations! You has defeated one poison enemy!");
    MyPEnemy* obj = (MyPEnemy*) sender();
    aw.at(obj->getYPos()*col+obj->getXPos())->setValue(std::numeric_limits<float>::infinity());

    for (std::vector< MyEnemy* >::iterator eneDead = myEnemies.begin() ; eneDead != myEnemies.end(); ++eneDead){
        if(((*eneDead)->getXPos() == obj->getXPos())&&((*eneDead)->getYPos()==obj->getYPos())){
            delete (*eneDead);
        }
    }
}

void GameTerminal::poisonUser(float newLevel)
{
    MyPEnemy* obj = dynamic_cast<MyPEnemy *> (sender());
    if(qPow((user->getXPos()-obj->getXPos()),2)+qPow((user->getYPos()-obj->getYPos()),2)<=4){
        if(obj->poison()){
        if(user->getHealth() > newLevel){
            user->setHealth(user->getHealth()- newLevel/1000);
        }
        else{
            user->setHealth(0.00f);
        }
        }
        else{
            obj->setDefeated(true);
        }
    }
}

void GameTerminal::checkNewPos()
{
    output->appendPlainText(">>"+showProta());
    for(auto &enemy : myEnemies){
        if((enemy->getXPos() == user->getXPos())&&(enemy->getYPos() == user->getYPos())){
            if((user->getHealth()-enemy->getValue()) > 0){
            user->setHealth(user->getHealth()-enemy->getValue());
            user->setEnergy(100.00f);
            aw.at(col*enemy->getYPos()+enemy->getXPos())->setValue(std::numeric_limits<float>::infinity());
            enemy->setDefeated(true);
            }
            else{
                user->setHealth(0.0f);
                user->setEnergy(100.00f);
            }
        }
    }

    for(auto &enemy : myPEnemies){
        if((enemy->getXPos() == user->getXPos())&&(enemy->getYPos() == user->getYPos())){
            if((user->getHealth()-enemy->getValue()) > 0){
            user->setHealth(user->getHealth()-enemy->getValue());
            user->setEnergy(100.00f);
            aw.at(col*enemy->getYPos()+enemy->getXPos())->setValue(std::numeric_limits<float>::infinity());
           // emit myModel->myProtagonist->encounterPenemy();
            }
            else{
                user->setHealth(0.0f);
                user->setEnergy(100.00f);
            }
        }
    }

    if(addHealth(user->getXPos(),user->getYPos())){
        output->appendPlainText("   Congratulations! You get a health pack and your health is "+QString::number(user->getHealth())+" now");
    }

    moveEnemy();

}

void GameTerminal::checkHealth()
{
    if(user->getHealth() == 0){
        emit myModel->myProtagonist->protagonistDead();
    }
}

void GameTerminal::checkEnergy()
{
    if(user->getEnergy() == 0){
        emit myModel->myProtagonist->protagonistDead();
    }
}


