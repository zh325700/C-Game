#include <QApplication>
#include <QWidget>
#include "Game.h"
#include "MainWindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    QWidget myWindow = new QWidget();
//    game = new Game();
    MainWindow w;
    w.show();

    return a.exec();
}
