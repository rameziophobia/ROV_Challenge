#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "rovtimer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();
    void updateTimeLabel(QString newTime);

private:
    Ui::MainWindow *ui;
    RovTimer * rovTimer;
};

#endif // MAINWINDOW_H
