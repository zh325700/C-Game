#-------------------------------------------------
#
# Project created by QtCreator 2017-11-16T21:25:50
#
#-------------------------------------------------

QT       += core gui \
            multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = team104
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    MyEnemy.cpp \
    MyProtagonist.cpp \
    MyTile.cpp \
    MyPEnemy.cpp \
    HealthPack.cpp \
    MainWindow.cpp \
    Graphics_view_zoom.cpp \
    MyModel.cpp \
    Astar.cpp \
    Node.cpp \
    GraphicGameView.cpp \
    TerminalGameView.cpp \
    Customdialog.cpp

HEADERS += \
    MyEnemy.h \
    MyProtagonist.h \
    MyTile.h \
    MyPEnemy.h \
    HealthPack.h \
    MainWindow.h \
    Graphics_view_zoom.h \
    MyModel.h \
    TerminalGameView.h\
    Astar.h \
    Node.h \
    GraphicGameView.h \
    Customdialog.h


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libworld/release/ -lworld
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libworld/debug/ -lworld
else:unix: LIBS += -L$$PWD/libworld/ -lworld

INCLUDEPATH += $$PWD/libworld
DEPENDPATH += $$PWD/libworld

RESOURCES += \
    res.qrc
