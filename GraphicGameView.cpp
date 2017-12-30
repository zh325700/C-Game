#include <memory>
#include <QTimer>
#include <QImage>
#include <QGraphicsTextItem>
#include <iostream>
#include <vector>
#include <QDebug>
#include <typeinfo>
#include <QGraphicsEllipseItem>
#include <QColor>
#include <QGraphicsScene>
#include <QPixmap>
#include <QPoint>
#include <QPointF>
#include <QGraphicsSceneMouseEvent>

#include <QDrag>
#include <QMimeData>
#include <QPainter>
#include <QLabel>

#include "GraphicGameView.h"
#include "Graphics_view_zoom.h"
#include "MainWindow.h"





//in order to use media , you have to add "multimedia" in
//the .pro file

extern MyModel *myModel;

GraphicGameView::GraphicGameView()
{

    this->setMultipleSizeOfCircle(1);
    ellipse = new QGraphicsEllipseItem();

    // create the scene
    scene = new QGraphicsScene((QGraphicsView *)this);
    scene->setSceneRect(0,0,20000,20000); // make the scene 800x600 instead of infinity by infinity (default)

    // make the newly created scene the scene to visualize (since Game is a QGraphicsView Widget,
    // it can be used to visualize scenes)
    setScene(scene);
    setFixedSize(800,600);

    //add auto zoom in and out
    Graphics_view_zoom* z = new Graphics_view_zoom(this);
    z->set_modifiers(Qt::NoModifier);
}

GraphicGameView::~GraphicGameView()
{
    // delete all memories
}

void GraphicGameView::initialGraphicView()
{
    myModel->getMyProtagonist()->QGraphicsItem::setPos(myModel->getMyProtagonist()->getXPos()*myModel->getMyProtagonist()->getSizeOfTile(),
                                                       myModel->getMyProtagonist()->getYPos()*myModel->getMyProtagonist()->getSizeOfTile());

    myModel->getMyProtagonist()->setFlag(QGraphicsItem::ItemIsFocusable);
    myModel->getMyProtagonist()->setFocus();


    //add Tiles to the scene and connect
    for(auto &aTile:myModel->getMyTilesMap()){
        scene->addItem(aTile);
    }
    //add pack to the scene and connect
    for(auto &aPack:myModel->getMyHealthPacks()){
         scene->addItem(aPack);
    }
    // add the Enemies to the scene
    for(auto &aEnemy:myModel->getMyEnemies()){
         scene->addItem(aEnemy);
    }

    //add pEnemies to the scene and connect
    for(auto &aPEnemy:myModel->getMyPEnemies()){
         scene->addItem(aPEnemy);
    }
    // add the protagonist to the scene
    scene->addItem(myModel->getMyProtagonist());


    //center the prota
    centerOn(myModel->getMyProtagonist());


    //make signal and slot connect of Enemies
    for(auto &aEnemy:myModel->getMyEnemies()){
         int x=aEnemy->getXPos();
         int y=aEnemy->getYPos();
         QObject::connect(aEnemy,SIGNAL(dead()),myModel->getMyTilesMap()[x+y*myModel->getCols()],SLOT(drawBlack()));
         QObject::connect(aEnemy,SIGNAL(dead()),this,SLOT(deleteEnemy()));
    }

    //make signal and slot connect of Penemies
    for(auto &aPEnemy:myModel->getMyPEnemies()){
         int x=aPEnemy->getXPos();
         int y=aPEnemy->getYPos();
         QObject::connect(aPEnemy,SIGNAL(dead()),myModel->getMyTilesMap()[x+y*myModel->getCols()],SLOT(drawBlack()));
         QObject::connect(aPEnemy,SIGNAL(dead()),this,SLOT(deletePnemy()));
         QObject::connect(myModel->getMyProtagonist(),&MyProtagonist::encounterPenemy,this,&GraphicGameView::drawPoinsonCircle);
         QObject::connect(aPEnemy,&MyPEnemy::poisonLevelUpdated,myModel->getMyProtagonist(),&MyProtagonist::ifInPoisonarea);
         QObject::connect(aPEnemy,&MyPEnemy::poisonLevelUpdated,this,&GraphicGameView::changeCircleColor);
    }
}

void GraphicGameView::drawPoinsonCircle()
{

    if(!myModel->getMyProtagonist()->getAlReadyDrawCircle()){
        //add one circle to the scene the x,y is based on protagoinist current position
        setMultipleSizeOfCircle(2);
        int xCircle = myModel->getMyProtagonist()->getXPos()*myModel->getMyProtagonist()->getSizeOfTile() - multipleSizeOfCircle*myModel->getMyProtagonist()->getSizeOfTile() ;
        int yCircle = myModel->getMyProtagonist()->getYPos()*myModel->getMyProtagonist()->getSizeOfTile() - multipleSizeOfCircle*myModel->getMyProtagonist()->getSizeOfTile();
        float widthOfCircle = 2*(0.5 + multipleSizeOfCircle)*myModel->getMyProtagonist()->getSizeOfTile();
        float heightOfCircle = widthOfCircle;

        //set brush to the poison circle
        QBrush *brush = new QBrush();
        brush->setStyle(Qt::CrossPattern);
        brush->setColor(Qt::magenta);
        ellipse->setRect(xCircle,yCircle,widthOfCircle,heightOfCircle);
        ellipse->setBrush(*brush);
        scene->addItem(ellipse);
    }
        myModel->getMyProtagonist()->setAlReadyDrawCircle(true);

}

void GraphicGameView::deletePnemy()
{
    myModel->getMyProtagonist()->setAlReadyDrawCircle(false);
    scene->removeItem(ellipse);
    setPoisonLevelcount(0);
    MyPEnemy * deadPenemy = dynamic_cast<MyPEnemy *>(sender());
    if(deadPenemy){
        scene->removeItem(deadPenemy);
        delete deadPenemy;
        for(unsigned i=0;i<myModel->getMyPEnemies().size();i++){
            if(myModel->getMyPEnemies()[i] == deadPenemy){
                myModel->getMyPEnemies().erase(myModel->getMyPEnemies().begin()+i);
            }
        }

//        qDebug()<<"PEnemy is deleted";
    }


}

void GraphicGameView::deleteEnemy()
{
        MyEnemy *deadEnemy =dynamic_cast<MyEnemy *> (sender());
        if(deadEnemy){
            scene->removeItem(deadEnemy);
            delete deadEnemy;
            for(unsigned i=0;i<myModel->getMyEnemies().size();i++){
                if(myModel->getMyEnemies()[i] == deadEnemy){
                    myModel->getMyEnemies().erase(myModel->getMyEnemies().begin()+i);
                }
            }
        }

}

void GraphicGameView::drawThePath(int speed)
{

    //MyModel *tempM = myModel;    //for testing purpose
    for(int i = myModel->getMyAstar()->getSolution().size()-1;i>=0;i--){
        int x = myModel->getMyAstar()->getSolution()[i]->getPos_x();
        int y = myModel->getMyAstar()->getSolution()[i]->getPos_y();
        QGraphicsPixmapItem *aTile =  new QGraphicsPixmapItem();
        aTile->setPos(x*myModel->getMyProtagonist()->getSizeOfTile(),y*myModel->getMyProtagonist()->getSizeOfTile());
        aTile->setPixmap(QPixmap(":/images/icons/coin.gif"));
        pathTiles.push_back(aTile);
        scene->addItem(aTile);

    }
    myModel->getMyProtagonist()->timer->start(speed);

}

void GraphicGameView::changeCircleColor()
{
//        float widthOfCircle = 2*(0.5 + getMultipleSizeOfCircle())*myModel->getMyProtagonist()->getSizeOfTile();
//        float heightOfCircle = widthOfCircle;
   vector<QColor> color = {Qt::magenta,Qt::blue,Qt::white,Qt::green,Qt::red,Qt::yellow,Qt::gray};
    QBrush *brush = new QBrush();
    brush->setStyle(Qt::CrossPattern);
    brush->setColor(color[getPoisonLevelcount()%7]);
    ellipse->setBrush(*brush);
    setPoisonLevelcount(getPoisonLevelcount()+1);
}



int GraphicGameView::getPoisonLevelcount() const
{
    return poisonLevelcount;
}

void GraphicGameView::setPoisonLevelcount(int value)
{
    poisonLevelcount = value;
}





std::vector<QGraphicsPixmapItem *> GraphicGameView::getPathTiles()
{
    return pathTiles;
}


int GraphicGameView::getMultipleSizeOfCircle() const
{
    return multipleSizeOfCircle;
}

void GraphicGameView::setMultipleSizeOfCircle(int value)
{
    multipleSizeOfCircle = value;
}


//Everything starts with a mouse press
void GraphicGameView::mousePressEvent(QMouseEvent * event)
  {
  //if not pressed on a label, simply return
  HealthPack *ahealthpack = dynamic_cast<HealthPack*>(itemAt(event->pos()));
  if (!ahealthpack)
    return;


  //store all necessary data of draggable object in byte array coupled to datastream
  QByteArray itemData;
  QDataStream dataStream(&itemData, QIODevice::WriteOnly);
  QPixmap pixmap = ahealthpack->pixmap();
  float value = ahealthpack->getValue();
  QPointF eventPoint = mapToScene(event->pos()) ;
  QPoint poiintHealthpack = QPoint(ahealthpack->pos().toPoint());
  QPoint offset = QPoint(eventPoint.toPoint() - ahealthpack->pos().toPoint());
  //in this example, the pixmap, the size of the label, the relative position of the label to the mouse
  dataStream << pixmap << value<< offset;
  //create the drag object
  QDrag *drag = new QDrag(this);
  //define MIMEtype of your data and add byte array to mimedata
  QMimeData *mimeData = new QMimeData;
  mimeData->setData("application/Demo-QLabeldata", itemData);
  drag->setMimeData(mimeData);
  //pixmap to show when draggin the object
  drag->setPixmap(ahealthpack->pixmap());
  //set hot-spot position = position of topleft corner of label
  drag->setHotSpot(eventPoint.toPoint() - ahealthpack->pos().toPoint());

  if(drag->exec(Qt::MoveAction | Qt::CopyAction) == Qt::MoveAction)
    delete ahealthpack;
  }

//describe behaviour while dragging
void GraphicGameView::dragMoveEvent(QDragMoveEvent *event)
  {
  //only process drags with this MIME type
  if (event->mimeData()->hasFormat("application/Demo-QLabeldata"))
    {
    event->accept();
    }
  else
    {
    event->ignore();
    }

  }

//describes behaviour if drag enters your application (here identical as move)
void GraphicGameView::dragEnterEvent(QDragEnterEvent *event)
  {
  if (event->mimeData()->hasFormat("application/Demo-QLabeldata"))
    {
    event->accept();
    }
  else
    {
    event->ignore();
    }
  }

//what to do if mouse is released when dragging
void GraphicGameView::dropEvent(QDropEvent *event)
  {
  //first check for MIME type
  if (event->mimeData()->hasFormat("application/Demo-QLabeldata"))
    {
    //get all needed data from byte array associated with event's mimeData
    QByteArray itemData = event->mimeData()->data("application/Demo-QLabeldata");
    QDataStream dataStream(&itemData, QIODevice::ReadOnly);

    QPixmap pixmap;
    QPoint offset;
    float value;
//    QSize labelSize;
    dataStream >> pixmap >> value >> offset;

    //create new QLabel at new position
    QPointF eventPoint = mapToScene(event->pos()) ;
    int x =round((eventPoint.toPoint() - offset).x());
    int y = round((eventPoint.toPoint() - offset).y());
    x = x/20;
    y = y/20;
    HealthPack *newHealthpack = new HealthPack(x,y,value);
    newHealthpack->setPixmap(pixmap);
    myModel->getMyHealthPacks().push_back(newHealthpack);
    scene->addItem(newHealthpack);

#ifdef SIMPLE
        event->setDropAction(Qt::MoveAction);
        event->accept();
#else
    if (event->source() == this)
      {
      event->setDropAction(Qt::MoveAction);
      event->accept();
      }
    else
      {
      event->setDropAction(Qt::CopyAction);
      event->accept();
      }
#endif
    }
  else
    {
    event->ignore();
    }
}











