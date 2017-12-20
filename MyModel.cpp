#include "MyModel.h"

MyModel::MyModel()
{
    std::shared_ptr<World> world = std::make_shared<World>();
    std::vector<std::unique_ptr<Tile>> mapTiles = world->createWorld(":/images/maps/worldmap.png");
    std::vector<std::unique_ptr<Tile>> healthpacks = world->getHealthPacks(500);
    std::vector<std::unique_ptr<Enemy>> enemiesFromWorld = world->getEnemies(50);
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
            myEnemies.push_back((aMyEnemy));
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
    for(auto &aEnemy:this->myEnemies){
         int x=aEnemy->getXPos();
         int y=aEnemy->getYPos();
         QObject::connect(aEnemy,SIGNAL(dead()),myTilesMap[x+y*cols],SLOT(drawBlack()));
         QObject::connect(aEnemy,SIGNAL(dead()),this,SLOT(deleteEnemy()));
    }

    //make signal and slot connect of Penemies
    for(auto &aPEnemy:this->myPEnemies){
         int x=aPEnemy->getXPos();
         int y=aPEnemy->getYPos();
         QObject::connect(aPEnemy,SIGNAL(dead()),this->myTilesMap[x+y*cols],SLOT(drawBlack()));
         QObject::connect(aPEnemy,SIGNAL(dead()),this,SLOT(deletePnemy()));
         QObject::connect(this->myProtagonist,&MyProtagonist::encounterPenemy,this,&Game::drawPoinsonCircle);
         QObject::connect(aPEnemy,&MyPEnemy::poisonLevelUpdated,myProtagonist,&MyProtagonist::ifInPoisonarea);
    }

}

MyModel::~MyModel()
{

}

bool MyModel::getWhichView() const
{
    return whichView;
}

void MyModel::setWhichView(bool value)
{
    whichView = value;
}

