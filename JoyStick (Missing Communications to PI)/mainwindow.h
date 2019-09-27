#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <joystick.h>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Joystick *myJoystick;
};

#endif // MAINWINDOW_H
