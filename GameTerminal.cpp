
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
    setWindowTitle("terminal");
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

    for(auto& ene:myEnemies){
           // connect(ene,&MyEnemy::dead,this,&GameTerminal::enemyDead);
            QObject::connect(ene,&MyEnemy::dead,this,&GameTerminal::enemyDead);
    }

    for(auto& pene:myPEnemies){
        connect(this,&GameTerminal::penemyDefeating,pene,&MyPEnemy::poison);
        connect(pene,&MyPEnemy::poisonLevelUpdated,this,&GameTerminal::poisonUser);
        connect(pene,&MyPEnemy::dead,this,&GameTerminal::penemyDead);
    }

}

GameTerminal::~GameTerminal(){}

void GameTerminal::init()
{
    speed = 1;
    helpText = "You can use command lines to do the following things: \n "
               "'show prota' get information of protagonist with \n"
               "'find enemy' find all enemies in this map \n"
               "'find health packs' find all health packswith \n"
               "defeat enemy with: 'defeat(xposition,yposition)' \n"
               "use 'a,w,s,d' in the keyboard to control the movement \n"
               "'speed(1)' you can choose the speed \n"
               "you can enter 'help' to get manual at any time";

    if(speed >1){
    boundary = "You are moving out of boundary, maybe you can slow your speed \n";
    existwall = "There is wall blocking your way, you cannot move in this direction. Maybe you can slow your speed\n";
    existEnemy = "There are enemies in the way, you cannot move. Maybe you can slow your speed\n";
    noEnergy = "You don't have enough energy to move at that fast speed!\n";
    }
    else{
        boundary = "You are moving out of boundary\n";
        existwall = "There is wall blocking your way, you cannot move in this direction\n";
        existEnemy = "There are enemies in the way, you cannot move\n";
        noEnergy = "You don't have enough energy to move\n";
    }
}

void GameTerminal::initWorld()
{
    nrEnemies = 2;
    nrPacks = 5;
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

    indicator = new QLabel("this is indicator:");

    auto mainLayout = new QGridLayout(this);
    mainLayout->addWidget(groupOutput);
    mainLayout->addWidget(group);
    mainLayout->addWidget(indicator);
}

void GameTerminal::uDead()
{
    output->appendPlainText(">>");

    if(user->getEnergy() <= 0){
        output->insertPlainText("you don't have any energy \n");
    }
    if(user->getHealth() <= 0){
        output->insertPlainText("you don't have any health \n");
    }

    output->insertPlainText("you are dead! press 'N' to start a new game!");

}

bool GameTerminal::addHealth(int x, int y)
{
    bool isHealth = false;
//            Tile * raw = healthPack.release();        // delete *healthPack;
//            delete raw;   // needs manual deletion

    for (std::vector< HealthPack* >::iterator healthPack = myHealthPacks.begin() ; healthPack != myHealthPacks.end(); ++healthPack){
        if(((*healthPack)->getXPos() == x)&&((*healthPack)->getYPos() == y)){
            user->setHealth(100.00f);
            isHealth = true;
            delete (*healthPack);
        }
    }

    return isHealth;
}

bool GameTerminal::movePos(QString direction)
{
    bool pos = false;

    if(direction=="left"){
        if((user->getXPos() - speed)>=0){
            pos = true;
        }
    }
    else if(direction=="right"){
        if((col-1) >= (user->getXPos() + speed)){
            pos = true;
        }
    }
    else if(direction=="up"){
        if((user->getYPos() - speed) >= 0){
            pos = true;
        }
    }
    else if(direction=="down"){
        if((row-1) >= (user->getYPos() +speed)){
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
            for(int w=1;w<speed+1;w++){
                noWall = noWall && (aw.at(user->getYPos()*col+user->getXPos()-w)->getValue() != std::numeric_limits<float>::infinity());
            }
        }
    }
    else if(direction=="right"){
        if(movePos(direction)){
            for(int w=1;w<speed+1;w++){
            noWall = noWall && (aw.at(user->getYPos()*col+user->getXPos()+w)->getValue() != std::numeric_limits<float>::infinity());
            }
        }
    }
    else if(direction=="up"){
        if(movePos(direction)){
            for(int w=1;w<speed+1;w++){
                noWall = noWall &&(aw.at((user->getYPos() - w)*col+user->getXPos())->getValue() != std::numeric_limits<float>::infinity());
            }
        }
    }
    else if(direction=="down"){
        if(movePos(direction)){
            for(int w=1;w<speed+1;w++){
                noWall = noWall && (aw.at((user->getYPos()+w)*col+user->getXPos())->getValue() != std::numeric_limits<float>::infinity());
            }
        }
    }

    return noWall;
}

bool GameTerminal::moveEnemy(QString direction)
{
    bool noEnemy = true;

    if(direction=="left"){
        for(int w=1;w<speed+1;w++){
            for(auto &enemy : myEnemies){
                if((enemy->getXPos() == user->getXPos()-w)&&(enemy->getYPos() == user->getYPos())){
                    noEnemy = false;
                }
            }

            for(auto &enemy : myPEnemies){
                if((enemy->getXPos() == user->getXPos()-w)&&(enemy->getYPos() == user->getYPos())){
                    noEnemy = false;
                }
            }
        }
    }
    else if(direction=="right"){
        for(int w=1;w<speed;w++){
            for(auto &enemy : myEnemies){
                if((enemy->getXPos() == user->getXPos()+w)&&(enemy->getYPos() == user->getYPos())){
                    noEnemy = false;
                }
            }

            for(auto &enemy : myPEnemies){
                if((enemy->getXPos() == user->getXPos()+w)&&(enemy->getYPos() == user->getYPos())){
                    noEnemy = false;
                }
            }
        }
    }
    else if(direction=="up"){
        for(int w=1;w<speed+1;w++){
            for(auto &enemy : myEnemies){
                if((enemy->getXPos() == user->getXPos())&&(enemy->getYPos() == user->getYPos()-w)){
                    noEnemy = false;
                }
            }

            for(auto &enemy : myPEnemies){
                if((enemy->getXPos() == user->getXPos())&&(enemy->getYPos() == user->getYPos()-w)){
                    noEnemy = false;
                }
            }
        }
    }
    else if(direction=="down"){
        for(int w=0;w<speed+1;w++){
            for(auto &enemy : myEnemies){
                if((enemy->getXPos() == user->getXPos())&&(enemy->getYPos() == user->getYPos()+w)){
                    noEnemy = false;
                }
            }

            for(auto &enemy : myPEnemies){
                if((enemy->getXPos() == user->getXPos())&&(enemy->getYPos() == user->getYPos()+w)){
                    noEnemy = false;
                }
            }
        }
    }

    return noEnemy;
}

float GameTerminal::totalEnergy(QString direction)
{
    float sum = 0;

    if(direction=="left"){
        if(movePos(direction)){
            for(int e=1;e<speed+1;e++){
                sum=sum+abs(aw.at(user->getYPos()*col+user->getXPos()-e)->getValue()-aw.at(user->getYPos()*col+user->getXPos()-(e-1))->getValue());
            }
        }
    }
    else if(direction=="right"){
        if(movePos(direction)){
            for(int e=1;e<speed+1;e++){
                sum=sum+abs(aw.at(user->getYPos()*col+user->getXPos()+e)->getValue()-aw.at(user->getYPos()*col+user->getXPos()+(e-1))->getValue());
            }
        }
    }
    else if(direction=="up"){
        if(movePos(direction)){
            for(int e=1;e<speed+1;e++){
                sum=sum+abs(aw.at((user->getYPos()-e)*col+user->getXPos())->getValue()-aw.at((user->getYPos()-(e-1))*col+user->getXPos())->getValue());
            }
        }
    }
    else if(direction=="down"){
        if(movePos(direction)){
            for(int e=1;e<speed+1;e++){
                sum=sum+abs(aw.at((user->getYPos()+e)*col+user->getXPos())->getValue()-aw.at((user->getYPos()+(e-1))*col+user->getXPos())->getValue());
            }
        }
    }

    sum = sum + speed * costOfStep;

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
                                   +"), his strength is "+strength+" .");
    }

    for(auto &penemy :myPEnemies){
        QString xPosition = QString::number(penemy->getXPos());
        QString yPosition = QString::number(penemy->getYPos());
        QString strength = QString::number(penemy->getValue());

        output->appendPlainText("A poison enemy is at the location ("+xPosition+","+yPosition
                                   +"), his strength is "+strength+" .");
    }
}

void GameTerminal::findNearEnemy()
{
    for(auto &enemy : myEnemies){

        QString xPosition = QString::number(enemy->getXPos());
        QString yPosition = QString::number(enemy->getYPos());
        QString strength = QString::number(enemy->getValue());

        if(abs(enemy->getXPos()-user->getXPos())<=10||abs(enemy->getYPos()-user->getYPos())<=10){
            output->appendPlainText("A normal enemy is at the location ("+xPosition+","+yPosition
                                   +"), his strength is "+strength+" .");
        }
    }

    for(auto &penemy :myPEnemies){
        QString xPosition = QString::number(penemy->getXPos());
        QString yPosition = QString::number(penemy->getYPos());
        QString strength = QString::number(penemy->getValue());

        if(abs(penemy->getXPos()-user->getXPos())<=10||abs(penemy->getYPos()-user->getYPos())<=10){
            output->appendPlainText("A poison enemy is at the location ("+xPosition+","+yPosition
                                   +"), his strength is "+strength+" .");
        }
    }
}

void GameTerminal::findAllHealth()
{
    for(auto &healthP : myHealthPacks){

        QString xPosition = QString::number(healthP->getXPos());
        QString yPosition = QString::number(healthP->getYPos());
        //QString strength = QString::number(enemy->getValue());

        output->appendPlainText("A health pack is at the location ("+xPosition+","+yPosition+").");
    }
}

void GameTerminal::findNearHealth()
{
    for(auto &healthP : myHealthPacks){

        QString xPosition = QString::number(healthP->getXPos());
        QString yPosition = QString::number(healthP->getYPos());
        //QString strength = QString::number(enemy->getValue());

        if(abs(healthP->getXPos()-user->getXPos())<=10||abs(healthP->getYPos()-user->getYPos())<=10){
            output->appendPlainText("A health pack is at the location ("+xPosition+","+yPosition+").");
        }

    }
}

QString GameTerminal::showProta()
{
    QString protaInfo = "prota is at ("
                    +QString::number(user->getXPos())+","+QString::number(user->getYPos())
                    +"), health is "+QString::number(user->getHealth())
                    +", energy is "+QString::number(user->getEnergy())+" .";

    return protaInfo;
}

void GameTerminal::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_A){
        QString direction = "left";
        QString health = "";
        bool movable = ((movePos(direction))&&(movenoWall(direction))&&(moveEnemy(direction)));
        if(movable){
            if(moveEnergy(direction)){
                user->setEnergy(user->getEnergy()-totalEnergy(direction));
                user->Protagonist::setPos((user->getXPos()-speed),user->getYPos());
                }
            else{
                user->setEnergy(0.0f);
                user->Protagonist::setPos((user->getXPos()-speed),user->getYPos());
                uDead();
            }
        if(addHealth(user->getXPos(),user->getYPos())){
            health = "Congratulations! You get a health pack!\n";
        }
        output->appendPlainText(">>"+health+showProta());
        }
        else{
            QString unmove="";
            if(!movePos(direction)){
                unmove = unmove+boundary;
            }
            if(!movenoWall(direction)){
                unmove = unmove+existwall;
            }
            if(!moveEnemy(direction)){
                unmove = unmove+existEnemy;
            }
//            if(!moveEnergy(direction)){
//                unmove = unmove+noEnergy;
//            }
            output->appendPlainText(">>"+unmove);
        }
    }
    else if(event->key() == Qt::Key_D){
        QString direction = "right";
        QString health = "";
        bool movable = ((movePos(direction))&&(movenoWall(direction))&&(moveEnemy(direction)));
        if(movable){
            if(moveEnergy(direction)){
                user->setEnergy(user->getEnergy()-totalEnergy(direction));
                user->Protagonist::setPos((user->getXPos()+speed),user->getYPos());
            }
            else{
                user->setEnergy(0.0f);
                user->Protagonist::setPos((user->getXPos()+speed),user->getYPos());
                uDead();
            }
            if(addHealth(user->getXPos(),user->getYPos())){
            health = "Congratulations! You get a health pack, your health is full now!\n";
        }
        output->appendPlainText(">>"+health+showProta());
        }
        else{
            QString unmove="";
            if(!movePos(direction)){
                unmove = unmove+boundary;
            }
            if(!movenoWall(direction)){
                unmove = unmove+existwall;
            }
            if(!moveEnemy(direction)){
                unmove = unmove+existEnemy;
            }
//            if(!moveEnergy(direction)){
//                unmove = unmove+noEnergy;
//            }
            output->appendPlainText(">>"+unmove);
        }
    }
    else if(event->key() == Qt::Key_W){
        QString direction = "up";
        QString health = "";
        bool movable = ((movePos(direction))&&(movenoWall(direction))&&(moveEnemy(direction)));
        if(movable){
            if(moveEnergy(direction)){
                user->setEnergy(user->getEnergy()-totalEnergy(direction));
                user->Protagonist::setPos(user->getXPos(),(user->getYPos()-speed));
                }
            else{
                user->setEnergy(0.0f);
                user->Protagonist::setPos(user->getXPos(),(user->getYPos()-speed));
                uDead();
            }

        if(addHealth(user->getXPos(),user->getYPos())){
            health = "Congratulations! You get a health pack!\n";
        }
        output->appendPlainText(">>"+health+showProta());
        }
        else{
            QString unmove="";
            if(!movePos(direction)){
                unmove = unmove+boundary;
            }
            if(!movenoWall(direction)){
                unmove = unmove+existwall;
            }
            if(!moveEnemy(direction)){
                unmove = unmove+existEnemy;
            }
//            if(!moveEnergy(direction)){
//                unmove = unmove+noEnergy;
//            }
            output->appendPlainText(">>"+unmove);
        }
    }
    else if(event->key() == Qt::Key_S){
        QString direction = "down";
        QString health= "";
        bool movable = ((movePos(direction))&&(movenoWall(direction))&&(moveEnemy(direction)));
        if(movable){
            if(moveEnergy(direction)){
                user->setEnergy(user->getEnergy()-totalEnergy(direction));
                user->Protagonist::setPos(user->getXPos(),(user->getYPos()+speed));
            }
            else{
                user->setEnergy(0.0f);
                user->Protagonist::setPos(user->getXPos(),(user->getYPos()+speed));
                uDead();
            }
        if(addHealth(user->getXPos(),user->getYPos())){
            health = "Congratulations! You get a health pack!\n";
        }
        output->appendPlainText(">>"+health+showProta());
        }
        else{
            QString unmove="";
            if(!movePos(direction)){
                unmove = unmove+boundary;
            }
            if(!movenoWall(direction)){
                unmove = unmove+existwall;
            }
            if(!moveEnemy(direction)){
                unmove = unmove+existEnemy;
            }
//            if(!moveEnergy(direction)){
//                unmove = unmove+noEnergy;
//            }
            output->appendPlainText(">>"+unmove);
        }
    }
    else if(event->key() == Qt::Key_Up){
        if(inputPosition >0){
        lineEdit->setText(inputs.at(inputPosition-1));
        inputPosition = inputPosition-1;
        }
        else{
            lineEdit->setText(inputs.at(inputs.size()-1));
            inputPosition = inputs.size()-1;
        }
    }

    else if(event->key() == Qt::Key_Down){
        if(inputPosition<inputs.size()-1){
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

    else if(input=="find enemy"){
        output->appendPlainText(">> there are "+QString::number(nrEnemies)+" enemies in this world, the locations are following:") ;
        findAllEnemy();
        lineEdit->clear();
    }

    else if(input=="find near enemy"){
        output->appendPlainText(">> there are "+QString::number(nrEnemies)+" enemies in this world, the locations are following:") ;
        findNearEnemy();
        lineEdit->clear();
    }

    else if(input == "find health packs"){
        output->appendPlainText(">> there are " +QString::number(myHealthPacks.size())+" health packs in this world now.");
        findAllHealth();
        lineEdit->clear();
    }

    else if(input == "find near health packs"){
        output->appendPlainText(">> there are " +QString::number(myHealthPacks.size())+" health packs in this world now.");
        findNearHealth();
        lineEdit->clear();
    }

    else if((input.startsWith(("speed("),Qt::CaseSensitive))&&(input.endsWith((")"),Qt::CaseSensitive))){
        int index1 = 0;
        index1 = input.indexOf(")");
        if(index1 !=0){
            bool okS;
            int newSpeed = input.mid(6,index1-6).toInt(&okS);
            if(okS){
                if(newSpeed>5){
                    output->appendPlainText(">> you cannot choose the too fast speed!");
                }
                else if(newSpeed == speed){
                    output->appendPlainText(">> you did not change speed");
                }
                else if((newSpeed<=5)&&(newSpeed>=1)&&(newSpeed!=speed)){
                    speed = newSpeed;
                    output->appendPlainText(">> speed is changed, the current speed is "+QString::number(speed));
                }
                else{
                    output->appendPlainText(">> invalid number to be used as a new speed, "
                                            "you need to input an integer which is larger or equal to 1"
                                            "and smaller than 6");
                }
            }
            else{
                output->appendPlainText(">> invalid command to change speed! invalid number between the brackets");
            }
        }
        else{
            output->appendPlainText(">> invalid command foramt! please use the format 'speed(1)'\n");
        }
        lineEdit->clear();
    }

    else if((input.startsWith(("defeat("),Qt::CaseSensitive))&&(input.endsWith((")"),Qt::CaseSensitive))&&(input.contains(","))){
        int index1 = 0;
        int index2 = 0;
        int index3 = 0;
        index1 = input.indexOf("(");
        index2 = input.indexOf(",");
        index3 = input.indexOf(")");

        if((index1!=0)&&(index2!=0)&&(index3!=0)){
            bool find = false;
            bool okX;
            bool okY;
            int enemyX = input.mid((index1+1),(index2-index1-1)).toInt(&okX);
            int enemyY = input.mid((index2+1),(index3-index2-1)).toInt(&okY);

            if(okX && okY){
            //check whether an enemy is at the position
                for( auto& tEnemy : myEnemies){
                    if((tEnemy->getXPos() == enemyX)&&(tEnemy->getYPos() == enemyY)){
                        if((abs(user->getXPos()-enemyX)==1)||(abs(user->getYPos()-enemyY)==1)){
                                if(user->getHealth() > tEnemy->getValue()){
                                    user->setHealth(user->getHealth()-(tEnemy->getValue()));
                                    user->setEnergy(100.00f);
                                    tEnemy->setDefeated(true);
                                   // output->appendPlainText(">> Congratulations! You has defeated one enemy!\n");
                                }
                                else{
                                    user->setHealth(0.00f);
                                    uDead();
                                }
                            }
                            else{
                            output->appendPlainText(">> You cannot defeat this enemy because you are too far away from enemy!");
                            }

                             find = true;
                        }
                }

                for( auto& tPEnemy : myPEnemies){
                    if((tPEnemy->getXPos() == enemyX)&&(tPEnemy->getYPos() == enemyY)){
                        if((abs(user->getXPos()-enemyX)==1)||(abs(user->getYPos()-enemyY)==1)){
                                if(user->getHealth() > tPEnemy->getValue()){
                                    user->setHealth(user->getHealth()-(tPEnemy->getValue()));
                                    user->setEnergy(100.00f);
                                    //tPEnemy->setDefeated(true);
                                    emit penemyDefeating();
                                }
                                else{
                                    user->setHealth(0.00f);
                                    uDead();
                                }
                            }
                            else{
                            output->appendPlainText(">> You cannot defeat this enemy because you are too far away from enemy!");
                            }

                             find = true;
                        }
                }

             if(!find){
                 output->appendPlainText(">> no enemy at this location");
            }
        }
        else{
            output->appendPlainText(">> invalid input for the location of enemy, please use the format 'defeat(xposition,yposition)'"
                                    "the xposition and yposition should be integers\n");
        }
            lineEdit->clear();
    }
        else{
            output->appendPlainText(">> invalid command foramt! please use the format 'defeat(xposition,yposition)'\n");
        }
    }
    else{
        output->appendPlainText(">> invalid command, please enter 'help' to get more information");
        lineEdit->clear();
    }
    QFont font = indicator->font();
    font.setBold(true);
    indicator->setFont(font);
    indicator->setStyleSheet("color:red");
}

void GameTerminal::enemyDead()
{
    qDebug()<<"xuqingjie paole";
    output->appendPlainText(">> Congratulations! You has defeated one enemy!");
    MyEnemy* obj = (MyEnemy*) sender();
    aw.at(obj->getYPos()*col+obj->getXPos())->setValue(std::numeric_limits<float>::infinity());

    for (std::vector< MyEnemy* >::iterator eneDead = myEnemies.begin() ; eneDead != myEnemies.end(); ++eneDead){
        if(((*eneDead)->getXPos() == obj->getXPos())&&((*eneDead)->getYPos()==obj->getYPos())){
            delete (*eneDead);
        }
    }
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
    MyPEnemy* obj = (MyPEnemy*) sender();
    if(qPow((user->getXPos()-obj->getXPos()),2)+qPow((user->getYPos()-obj->getYPos()),2)<=4){
        if(obj->poison()){
        if(user->getHealth() > newLevel){
            user->setHealth(user->getHealth()- newLevel/1000);
        }
        else{
            user->setHealth(0.00f);
            uDead();
        }
        }
        else{
            obj->setDefeated(true);
        }
    }
}


