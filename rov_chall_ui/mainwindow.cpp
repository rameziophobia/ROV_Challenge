#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rovtimer.h"
#include <QtDebug>
#include <QProcess>

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
    ui->timer_lbl->setText(newTime);
}


void MainWindow::on_startTimer_btn_clicked()
{
    rovTimer->start();
}

void MainWindow::on_keyBindings_btn_clicked()
{
    keyBindings k;
    k.exec();
}

void MainWindow::on_switchCameras_btn_clicked()
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


///
/// \brief MainWindow::run_script
/// \param arguments of the python code as a QStringList
/// \return returns the script's standard output
///
QString MainWindow::run_script(QStringList params)
{
    QProcess process;
    process.start(PYTHON_VERSION, params);
    process.waitForFinished(-1);
//    qDebug() << process.readAllStandardError();
//    qDebug() << process.readAllStandardOutput();
    return process.readAllStandardOutput();
}

void MainWindow::box_script(QString boxNum)
{
//    TODO add gaussian kernal size as input
    QStringList params;

    QString img_path = R"(/media/ramez/OS/Ramez/programming/code/Qt/rov_chall_ui/python_scripts/testing/shapes.png)";
    params << SCRIPTS_PATH + "shapes.py" << "--box" << boxNum << "--image" << img_path;

    QString out = run_script(params);
    ui->boxInfo_lbl->setText(out);
}

void MainWindow::on_box1Detect_btn_clicked()
{
    box_script("b1");
}

void MainWindow::on_box2Detect_btn_clicked()
{
    box_script("b2");
}

void MainWindow::on_box3Detect_btn_clicked()
{
    box_script("b3");
}

void MainWindow::on_compareBoxes_btn_clicked()
{
    ui->box1Detect_btn->setStyleSheet(QString(""));
    ui->box2Detect_btn->setStyleSheet(QString(""));
    ui->box3Detect_btn->setStyleSheet(QString(""));

    QString odd_box = run_script(QStringList(SCRIPTS_PATH + "compare_shapes.py"));

    if(odd_box == "b1"){
        ui->box1Detect_btn->setStyleSheet(QString("QPushButton {background-color: red;}"));
        ui->boxInfo_lbl->setText("box 1 is different");
    }else if (odd_box == "b2") {
        ui->box2Detect_btn->setStyleSheet(QString("QPushButton {background-color: red;}"));
        ui->boxInfo_lbl->setText("box 2 is different");
    }else if (odd_box == "b3") {
        ui->box3Detect_btn->setStyleSheet(QString("QPushButton {background-color: red;}"));
        ui->boxInfo_lbl->setText("box 3 is different");
    }else {
        ui->boxInfo_lbl->setText("ERROR");
    }
}
