#ifndef GraphicGameView_H
#define GraphicGameView_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <memory>
#include <QObject>
#include <QPointF>

#include <QMouseEvent>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>


#include "MyEnemy.h"
#include "MyProtagonist.h"
#include "MyTile.h"
#include "MyPEnemy.h"
#include "MyEnemy.h"
#include "HealthPack.h"
#include "MainWindow.h"
#include "world.h"
#include "MyModel.h"

class GraphicGameView: public QGraphicsView{
    Q_OBJECT
    //give game referance to scene,player,score,health
public:
    GraphicGameView();
    ~GraphicGameView();
    QGraphicsScene * scene;
//    MyEnemy *myEnemy;
    QGraphicsEllipseItem *ellipse;
    int getMultipleSizeOfCircle() const;
    void setMultipleSizeOfCircle(int value);

    QPointF getEndPoint() const;
    std::vector<QGraphicsPixmapItem *> pathTiles={};
    std::vector<QGraphicsPixmapItem *> getPathTiles() ;


    int getPoisonLevelcount() const;
    void setPoisonLevelcount(int value);
    void initialGraphicView();
//    void makeConnectionsGraphicView();

    //drag and drop
    void mousePressEvent(QMouseEvent *);
    void dragEnterEvent(QDragEnterEvent *);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);



public slots:
    void drawPoinsonCircle();
    void deletePnemy();
    void deleteEnemy();
    void drawThePath();
    void changeCircleColor();
    void changeTimer();

signals:


private:
    int multipleSizeOfCircle;
    int poisonLevelcount=0;
    QPointF endPoint ;

};

#endif // GraphicGameView_H
