#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QWidget>
#include <QGroupBox>

class MainWindow: public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent =0);
    ~MainWindow();
    QHBoxLayout *layout;
    QLabel *healthLabel;
    QLineEdit * healthValue;
    QLabel * energyLable;
    QLineEdit* energyValue;
    QGroupBox* healthgroup;
    QHBoxLayout* layoutStatistic;
public slots:
    void refreshEandH();
};

#endif // MAINWINDOW_H
