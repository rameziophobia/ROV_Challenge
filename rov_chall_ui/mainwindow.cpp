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

    player2 = new QMediaPlayer(this);
    player1 = new QMediaPlayer(this);

    vwmain = new QVideoWidget(this);
    vwsecondary = new QVideoWidget(this);

    player1->setVideoOutput(vwmain);
    player2->setVideoOutput(vwsecondary);

    player1->setMedia(QUrl("https://raw.githubusercontent.com/mediaelement/mediaelement-files/master/big_buck_bunny.mp4"));
    player2->setMedia(QUrl("http://techslides.com/demos/sample-videos/small.mp4"));

    player1->setMuted(true);
    player2->setMuted(true);

    vwmain->setGeometry(10,10,832,468);
    vwsecondary->setGeometry(870,10,400,225);
    switched = false;

    vwmain->show();
    vwsecondary->show();

    player1->play();
    player2->play();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTimeLabel(QString newTime)
{
    ui->timerlabel->setText(newTime);
}

void MainWindow::on_switchCameras_clicked()
{
    if(switched){
        vwmain->setGeometry(10,10,832,468);
        vwsecondary->setGeometry(870,10,400,225);
        switched = false;
    }
    else{
        vwsecondary->setGeometry(10,10,832,468);
        vwmain->setGeometry(870,10,400,225);
        switched = true;
    }
}

void MainWindow::on_startTimer_clicked()
{
    rovTimer->start();
}

void MainWindow::on_keyBindings_clicked()
{
    keyBindings k;
    k.exec();
}
