#ifndef GraphicGameView_H
#define GraphicGameView_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <memory>
#include <QObject>
#include <QPointF>

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
    void mousePressEvent(QMouseEvent *event);

    QPointF getEndPoint() const;
    std::vector<QGraphicsPixmapItem *> pathTiles ={};
    std::vector<QGraphicsPixmapItem *> getPathTiles() ;



public slots:
    void drawPoinsonCircle();
    void deletePnemy();
    void deleteEnemy();
    void drawThePath(int speed);

signals:
    void destinationFound();

private:
    int multipleSizeOfCircle;
    QPointF endPoint ;
    QMediaPlayer *music;
    QMediaPlaylist *playlist = new QMediaPlaylist();
};

#endif // GraphicGameView_H
