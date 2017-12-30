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

    QGraphicsScene * scene;
    QGraphicsEllipseItem *ellipse;
    std::vector<QGraphicsPixmapItem *> pathTiles={};

    GraphicGameView();
    ~GraphicGameView();

    void initialGraphicView();

    /*drag and drop of healthpack*/
    void mousePressEvent(QMouseEvent *);
    void dragEnterEvent(QDragEnterEvent *);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);

    /*getters and setters*/
    int getMultipleSizeOfCircle() const;
    void setMultipleSizeOfCircle(int value);
    QPointF getEndPoint() const;
    int getPoisonLevelcount() const;
    void setPoisonLevelcount(int value);
    std::vector<QGraphicsPixmapItem *> getPathTiles();


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
