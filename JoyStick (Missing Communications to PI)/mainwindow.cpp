#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    myJoystick = new Joystick();
}

MainWindow::~MainWindow()
{

}
