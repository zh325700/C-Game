#include "mainwindow.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
<<<<<<< HEAD
    std::cout<<"nihao";
=======

    qDebug() << "Hello world";
   std::cout<<"nihao";

>>>>>>> shuaigehan_qt
    return a.exec();
}
