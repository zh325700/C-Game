#include "MyModel.h"
#include <QtCore>
#include <QSettings>
#include <QTime>
#include <QDebug>


MyModel::MyModel(QString map)
{
    world = std::make_shared<World>();
    mapTiles = world->createWorld(map);
}

MyModel::~MyModel()
{

}

void MyModel::modelInitialize()
{
    std::vector<std::unique_ptr<Tile>> healthpacks = world->getHealthPacks(nrOfHealthPacks);
    std::vector<std::unique_ptr<Enemy>> enemiesFromWorld = world->getEnemies(nrOfEnemies);
    qDebug()<<"enemies in total: "<<nrOfEnemies;
    qDebug()<<"healthpacks in total: "<<nrOfHealthPacks;
    myProtagonist = new MyProtagonist();
    const std::type_info& typeE = typeid(Enemy);
    const std::type_info& typeP = typeid(PEnemy);

    cols = world->getCols();
    rows = world->getRows();


    // Give all the world tiles in Mymaptiles
    for ( auto &aTile: mapTiles){
        //Create MyTile class to be able to show the tiles
        int xPosition =aTile->getXPos();
        int yPositinon =aTile->getYPos();
        float blood =aTile->getValue();
        MyTile* aMyTile =new MyTile(xPosition,yPositinon,blood);        //Game have a vector of MyTile
        myTilesMap.push_back(aMyTile);                  //loop vector of MyTile through and add them to the scene
    }

    // Give all the Healthpacks in Myhealthpacks
    for(auto &aPack: healthpacks){
        int xhealth =aPack->getXPos();
        int yhealth =aPack->getYPos();
        float uselessValue =aPack->getValue();
        HealthPack *aMyHealthPack = new HealthPack(xhealth,yhealth,uselessValue);  //unexpected finished
        myHealthPacks.push_back(aMyHealthPack);
    }

    // judge what enemy type it is and copy its value to myEnemies and myPEnemies accordingly
    for(auto &unknowEnemy: enemiesFromWorld){
        const std::type_info& typeUnknow = typeid(*unknowEnemy);   //have to be * , I don't know why
        //push Enemies to myEnemies vector
        if(typeE.hash_code() == typeUnknow.hash_code()){
            int xEnemy = unknowEnemy->getXPos();
            int yEnemy =unknowEnemy->getYPos();
            float eStrength =unknowEnemy->getValue();
            MyEnemy *aMyEnemy = new MyEnemy(xEnemy,yEnemy,eStrength); //defeated is by default false, no need to pass
            myEnemies.push_back(aMyEnemy);
        }

        //push PEnemies to myPEnemies vector
        else if(typeP.hash_code() == typeUnknow.hash_code()){
            int xPEnemy = unknowEnemy->getXPos();
            int yPEnemy =unknowEnemy->getYPos();
            float pStrength =unknowEnemy->getValue();
            MyPEnemy *aMyPEnemy = new MyPEnemy(xPEnemy,yPEnemy,pStrength); //poisonlevel is strength here
            myPEnemies.push_back(aMyPEnemy);
        }

        //if it is not a Enemy, I don't know what to do
        else {
            qDebug() << "No Enemy";
        }
    }

    //make signal and slot connect of protagonist
    QObject::connect(this->myProtagonist,SIGNAL(posChanged(int,int)),this->myProtagonist,SLOT(moveToNextSpot()));
    QObject::connect(this->myProtagonist,SIGNAL(posChanged(int,int)),this->myProtagonist,SLOT(aquire_target()));
    QObject::connect(this->myProtagonist,&MyProtagonist::energyChanged,this->myProtagonist,&MyProtagonist::checkProtagonistDead);
    QObject::connect(this->myProtagonist,&MyProtagonist::healthChanged,this->myProtagonist,&MyProtagonist::checkProtagonistDead);

    //make signal and slot connect of enemies

    //initialize astar
    myAstar = std::make_shared<Astar>();

    //intialize readyToNext
    readyToNext = true;
}

bool MyModel::moveFast()
{
    QTime myTimer;
    myTimer.start();
    myAstar->find_path(myProtagonist->getXPos(),myProtagonist->getYPos(),destinationX,destinationY,mapTiles,rows,cols);
    int nMilliseconds = myTimer.elapsed();
    float nSeconds = (float)nMilliseconds / 1000;
    qDebug()<<"Astar executing time: "<<nSeconds<<"s";
    return myAstar->getIsFound();
}

bool MyModel::FindNextStep()
{
    nearestEnemy = findNearestEnemy();
    nearestPEnemy = findNearestPEnemy();

    //all enemy defeated
    if (nearestEnemy == nullptr && nearestPEnemy == nullptr)
    {
        return false;
    }

    //E + P
    else if(nearestEnemy != nullptr && nearestPEnemy != nullptr)
    {
        if(calculateDistance((*nearestEnemy)->getXPos(),(*nearestEnemy)->getYPos())
                < calculateDistance((*nearestPEnemy)->getXPos(),(*nearestPEnemy)->getYPos()))
        {
            gotoNextEnemy();
            return true;
        }
        else
        {
            gotoNextPEnemy();
            return true;
        }
    }

    //only P
    else if(nearestEnemy == nullptr && nearestPEnemy != nullptr)
    {
        gotoNextPEnemy();
        return true;
    }

    //only E
    else
    {
        gotoNextEnemy();
        return true;
    }


}

void MyModel::gotoNextEnemy()
{
    if(myProtagonist->getHealth() > (*nearestEnemy)->getValue())  //if health is enough to defeat the enemy -> go and fight
    {
        this->setDestinationX((*nearestEnemy)->getXPos());
        this->setDestinationY((*nearestEnemy)->getYPos());
        moveFast();
    }
    else                      //else -> find nearest health pack
    {
        nearestHP = findNearestHealthPack();
        if (nearestHP != nullptr)
        {
            this->setDestinationX((*nearestHP)->getXPos());
            this->setDestinationY((*nearestHP)->getYPos());
        }
        else   //no healthpacks anymore -> suicide
        {
            this->setDestinationX((*nearestEnemy)->getXPos());
            this->setDestinationY((*nearestEnemy)->getYPos());
        }
        moveFast();
    }
}

void MyModel::gotoNextPEnemy()
{
    if(myProtagonist->getHealth() > ((*nearestPEnemy)->getValue()) * 0.11)  //(1 + 0.1)/10
    {
        this->setDestinationX((*nearestPEnemy)->getXPos());
        this->setDestinationY((*nearestPEnemy)->getYPos());
        moveFast();
        (*nearestPEnemy)->setAlreadyDefeated(true);
    }
    else                      //else -> find nearest health pack
    {
        nearestHP = findNearestHealthPack();
        if (nearestHP != nullptr)
        {
            this->setDestinationX((*nearestHP)->getXPos());
            this->setDestinationY((*nearestHP)->getYPos());
        }
        else   //no healthpacks anymore -> suicide
        {
            this->setDestinationX((*nearestPEnemy)->getXPos());
            this->setDestinationY((*nearestPEnemy)->getYPos());
        }
        moveFast();
    }
}

MyEnemy **MyModel::findNearestEnemy()
{
    if (myEnemies.size() != 0)
    {
        MyEnemy ** wantedEnemy = new MyEnemy * ();
        int currentMinDistance = 0;
        wantedEnemy = &(myEnemies.front());
        currentMinDistance = calculateDistance((*wantedEnemy)->getXPos(),(*wantedEnemy)->getYPos());

        for (unsigned index = 0; index < myEnemies.size()-1; index++)
        {
            int distance = calculateDistance(myEnemies[index]->getXPos(),myEnemies[index]->getYPos());
            if (distance < currentMinDistance)
            {
                wantedEnemy = &(myEnemies[index]);
                currentMinDistance = distance;
            }
        }
        return wantedEnemy;
    }
    else return nullptr;
}

MyPEnemy **MyModel::findNearestPEnemy()
{
    if (myPEnemies.size() != 0)
    {
        MyPEnemy ** wantedPEnemy = new MyPEnemy * ();
        int currentMinDistance = INT_MAX;               //find the smallest
        if(myPEnemies.front()->getAlreadyDefeated()) {wantedPEnemy = nullptr;}
        else
        {
            wantedPEnemy = &(myPEnemies.front());
            currentMinDistance = calculateDistance((*wantedPEnemy)->getXPos(),(*wantedPEnemy)->getYPos());
        }

        for (unsigned index = 0; index < myPEnemies.size()-1; index++)
        {
            if(myPEnemies[index]->getAlreadyDefeated()) break;
            int distance = calculateDistance(myPEnemies[index]->getXPos(),myPEnemies[index]->getYPos());
            if (distance < currentMinDistance)
            {
                wantedPEnemy = &(myPEnemies[index]);
                currentMinDistance = distance;
            }
        }
        return wantedPEnemy;
    }
    else return nullptr;

}

HealthPack **MyModel::findNearestHealthPack()
{
    if (myHealthPacks.size() != 0)
    {
        HealthPack ** wantedHP = new HealthPack * ();
        int currentMinDistance = 0;
        wantedHP = &(myHealthPacks.front());
        currentMinDistance = calculateDistance((*wantedHP)->getXPos(),(*wantedHP)->getYPos());

        for (unsigned index = 0; index < myHealthPacks.size()-1; index++)
        {
            int distance = calculateDistance(myHealthPacks[index]->getXPos(),myHealthPacks[index]->getYPos());
            if (distance < currentMinDistance)
            {
                wantedHP = &(myHealthPacks[index]);
                currentMinDistance = distance;
            }
        }
        return wantedHP;
    }
    else return nullptr;
}

int MyModel::calculateDistance(int givenX, int givenY)
{
    int result = 0;
    result = abs(myProtagonist->getXPos() - givenX) + abs(myProtagonist->getYPos() - givenY);
    return result;
}


void MyModel::saveGame(QString filename)
{

    QSettings setting("Team104",filename);

    /*store filename into local file*/
    QFile file("save_filenames.txt");
    if (!file.open(QIODevice::Append | QIODevice::Text))
        return;
    QTextStream in(&file);
    in<<filename<<endl;


    setting.beginGroup("MyProtagonist");
    setting.setValue("protaX",this->myProtagonist->getXPos());
    setting.setValue("protaY",this->myProtagonist->getYPos());
    setting.setValue("protaHealth",this->myProtagonist->getHealth());
    setting.setValue("protaEnergy",this->myProtagonist->getEnergy());
    setting.setValue("protaSize",this->myProtagonist->getSizeOfTile());
    setting.setValue("protaPause",this->myProtagonist->getPaused());
    setting.endGroup();

    setting.beginGroup("MyEnemies");
    setting.beginWriteArray("Enemies");
    for (unsigned i = 0; i < myEnemies.size(); ++i) {
        setting.setArrayIndex(i);
        setting.setValue("EnemyX", myEnemies[i]->getXPos());
        setting.setValue("EnemyY", myEnemies[i]->getYPos());
        setting.setValue("EnemyValue", myEnemies[i]->getValue());
    }
    setting.endArray();
    setting.beginWriteArray("PEnemies");
    for (unsigned i = 0; i < myPEnemies.size(); ++i) {
        setting.setArrayIndex(i);
        setting.setValue("PEnemyX", myPEnemies[i]->getXPos());
        setting.setValue("PEnemyY", myPEnemies[i]->getYPos());
        setting.setValue("PEnemyValue", myPEnemies[i]->getValue());
    }
    setting.endArray();
    setting.endGroup();

    setting.beginGroup("MyTiles");
    setting.beginWriteArray("Tiles");
    for (unsigned i = 0; i < myTilesMap.size(); ++i) {
        setting.setArrayIndex(i);
        setting.setValue("TileX", myTilesMap[i]->getXPos());
        setting.setValue("TileY", myTilesMap[i]->getYPos());
        setting.setValue("TileValue", myTilesMap[i]->getValue());
    }
    setting.endArray();
    setting.endGroup();

    setting.beginGroup("MyHealthpacks");
    setting.beginWriteArray("Healthpacks");
    for (unsigned i = 0; i < myHealthPacks.size(); ++i) {
        setting.setArrayIndex(i);
        setting.setValue("HealthpackX", myHealthPacks[i]->getXPos());
        setting.setValue("HealthpackY", myHealthPacks[i]->getYPos());
        setting.setValue("HealthpackValue", myHealthPacks[i]->getValue());
    }
    setting.endArray();
    setting.endGroup();

}

void MyModel::loadGame(QString filename)
{
    QSettings  setting("Team104",filename);
    myEnemies.clear();
    myPEnemies.clear();

    setting.beginGroup("MyProtagonist");
    myProtagonist->Protagonist::setPos(setting.value("protaX").toInt(),setting.value("protaY").toInt());
    myProtagonist->setHealth(setting.value("protaHealth").toFloat());
    myProtagonist->setEnergy(setting.value("protaEnergy").toFloat());
    myProtagonist->setSizeOfTile(setting.value("protaSize").toInt());
    myProtagonist->setPaused(setting.value("protaPause").toBool());
    setting.endGroup();

    setting.beginGroup("MyEnemies");

    int sizeE = setting.beginReadArray("Enemies");
    for (int i = 0; i < sizeE; ++i) {
        setting.setArrayIndex(i);
        int xEnemy = setting.value("EnemyX").toInt();
        int yEnemy = setting.value("EnemyY").toInt();
        float eStrength =setting.value("EnemyValue").toFloat();;
        MyEnemy *aMyEnemy = new MyEnemy(xEnemy,yEnemy,eStrength);
        myEnemies.push_back(aMyEnemy);
    }
    setting.endArray();

    int sizeP = setting.beginReadArray("PEnemies");
    for (int i = 0; i < sizeP; ++i) {
        setting.setArrayIndex(i);
        int xPEnemy = setting.value("PEnemyX").toInt();
        int yPEnemy = setting.value("PEnemyY").toInt();
        float pStrength =setting.value("PEnemyValue").toFloat();;
        MyPEnemy *aPMyEnemy = new MyPEnemy(xPEnemy,yPEnemy,pStrength);
        myPEnemies.push_back(aPMyEnemy);
    }
    setting.endArray();
    setting.endGroup();

    setting.beginGroup("MyTiles");
    myTilesMap.clear();
    int sizeT = setting.beginReadArray("Tiles");
    for (int i = 0; i < sizeT; ++i) {
        setting.setArrayIndex(i);
        int xTile = setting.value("TileX").toInt();
        int yTile = setting.value("TileY").toInt();
        float Tvalue =setting.value("TileValue").toFloat();;
        MyTile *aTile = new MyTile(xTile,yTile,Tvalue);
        myTilesMap.push_back(aTile);
    }
    setting.endArray();
    setting.endGroup();

    setting.beginGroup("MyHealthpacks");
    myHealthPacks.clear();
    int sizeH = setting.beginReadArray("Healthpacks");
    for (int i = 0; i < sizeH; ++i) {
        setting.setArrayIndex(i);
        int xHealthpack = setting.value("HealthpackX").toInt();
        int yHealthpack = setting.value("HealthpackY").toInt();
        float valueHealthpack =setting.value("HealthpackValue").toFloat();;
        HealthPack *aTile = new HealthPack(xHealthpack,yHealthpack,valueHealthpack);
        myHealthPacks.push_back(aTile);
    }
    setting.endArray();
    setting.endGroup();

}

void MyModel::clearAllSaves()
{
    QString path = QDir::homePath()+"/.config/Team104";
    QDir dir(path);
    dir.setNameFilters(QStringList() << "*.*");
    dir.setFilter(QDir::Files);
    foreach(QString dirFile, dir.entryList())
    {
        dir.remove(dirFile);
    }
}



std::vector<MyEnemy *> & MyModel::getMyEnemies()
{
    return myEnemies;
}

void MyModel::setMyEnemies(std::vector<MyEnemy *> &value)
{
    myEnemies = value;
}

bool MyModel::getWhichView() const
{
    return whichView;
}

void MyModel::setWhichView(bool value)
{
    whichView = value;
}

int & MyModel::getCols()
{
    return cols;
}

void MyModel::setCols(int value)
{
    cols = value;
}

int & MyModel::getRows()
{
    return rows;
}

void MyModel::setRows(int value)
{
    rows = value;
}

MyProtagonist *MyModel::getMyProtagonist()
{
    return myProtagonist;
}

void MyModel::setMyProtagonist(MyProtagonist *value)
{
    myProtagonist = value;
}

std::vector<MyTile *> & MyModel::getMyTilesMap()
{
    return myTilesMap;
}

void MyModel::setMyTilesMap( std::vector<MyTile *> &value)
{
    myTilesMap = value;
}

std::vector<MyPEnemy *> & MyModel::getMyPEnemies()
{
    return myPEnemies;
}

void MyModel::setMyPEnemies( std::vector<MyPEnemy *> &value)
{
    myPEnemies = value;
}

std::vector<HealthPack *> & MyModel::getMyHealthPacks()
{
    return myHealthPacks;
}

void MyModel::setMyHealthPacks( std::vector<HealthPack *> &value)
{
    myHealthPacks = value;
}

int MyModel::getDestinationX() const
{
    return destinationX;
}

void MyModel::setDestinationX(int value)
{
    destinationX = value;
}

int MyModel::getDestinationY() const
{
    return destinationY;
}

void MyModel::setDestinationY(int value)
{
    destinationY = value;
}

std::shared_ptr<Astar> MyModel::getMyAstar() const
{
    return myAstar;
}

bool MyModel::getReadyToNext() const
{
    return readyToNext;
}

void MyModel::setReadyToNext(bool value)
{
    readyToNext = value;
}

float MyModel::getW() const
{
    return w;
}

void MyModel::setW(float value)
{
    w = value;

}

int MyModel::getNrOfEnemies() const
{
    return nrOfEnemies;
}

void MyModel::setNrOfEnemies(int value)
{
    nrOfEnemies = value;
}

int MyModel::getNrOfHealthPacks() const
{
    return nrOfHealthPacks;
}

void MyModel::setNrOfHealthPacks(int value)
{
    nrOfHealthPacks = value;
}

bool MyModel::getOnceOrMore() const
{
    return onceOrMore;
}

void MyModel::setOnceOrMore(bool value)
{
    onceOrMore = value;
}


int MyModel::getSpeed() const
{
    return speed;
}

void MyModel::setSpeed(int value)
{
    speed = value;
}

