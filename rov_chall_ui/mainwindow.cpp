#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rovtimer.h"
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    rovTimer = new RovTimer;
    connect(rovTimer, SIGNAL(timeChanged(QString)), this, SLOT(updateTimeLabel(QString)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTimeLabel(QString newTime)
{
    ui->my_lbl->setText(newTime);
}

void MainWindow::on_pushButton_2_clicked()
{
    rovTimer->start();
}
