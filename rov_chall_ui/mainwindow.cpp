#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rovtimer.h"
#include <QtDebug>
#include <QProcess>
#include <QMessageBox>
#include "../libs/rossubscriber.h"

inline std_msgs::String getRosString(std::string str) {
    std_msgs::String rs;
    rs.data = str;
    return rs;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    boxesPublisher("/rov_boxes", this),
    boxesSubscriber("/rov_boxes_info", &MainWindow::msgCallback, this, this),
    metalTypeClient(this)
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
    ui->boxInfo_lbl->setText("I'm Here");

    connect(&metalTypeClient, &GetMetalTypeClient::metalDetected, this, &MainWindow::metalTypeDetected);
    connect(&metalTypeClient, &GetMetalTypeClient::errorOccurred, this, &MainWindow::metalDetectionErrorOccurred);
    connect(ui->detectMetal_btn, &QPushButton::clicked, &metalTypeClient, &GetMetalTypeClient::metalTypeNeeded);
}

void MainWindow::metalTypeDetected(QString metalType) {
    ui->metalType_lbl->setText(metalType);
    ui->detectMetal_btn->setEnabled(true);
}

void MainWindow::metalDetectionErrorOccurred() {
    QMessageBox box;
    box.setText("ROV couldn't detect the type of metal");
    box.exec();
    ui->detectMetal_btn->setEnabled(true);
    ui->metalType_lbl->setText("");
}

void MainWindow::msgCallback(std_msgs::String msg) {
    ui->boxInfo_lbl->setText(msg.data.c_str());
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
    QString error = process.readAllStandardError();
    if (error != "")
        qDebug() << error;
//    qDebug() << process.readAllStandardOutput();
    return process.readAllStandardOutput();
}

void MainWindow::box_script(QString boxNum)
{
    QStringList params;

    QString img_path = R"(/media/ramez/OS/Ramez/programming/code/Qt/rov_chall_ui/python_scripts/testing/shapes.png)";
    params << SCRIPTS_PATH + "shapes.py" <<
              "--box" << boxNum <<
              "--image" << img_path <<
              "--kernal" << ui->kernalSize_lbl->text();

    QString out = run_script(params);
    ui->boxInfo_lbl->setText(out);
}

void MainWindow::on_box1Detect_btn_clicked()
{
    box_script("b1");
    boxesPublisher.send(getRosString("detectBox1"));
}

void MainWindow::on_box2Detect_btn_clicked()
{
    box_script("b2");
    boxesPublisher.send(getRosString("detectBox2"));
}

void MainWindow::on_box3Detect_btn_clicked()
{
    box_script("b3");
    boxesPublisher.send(getRosString("detectBox3"));
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

void MainWindow::on_countCoins_btn_clicked()
{
    QString kernalSize = ui->kernalSize_lbl->text();
    QString img_path = R"(/media/ramez/OS/Ramez/programming/code/Qt/rov_chall_ui/python_scripts/testing/coins3.jpeg)";
    QStringList params;
    params << SCRIPTS_PATH + "coin_detection.py" << "--image" << img_path << "--kernal" << kernalSize;

    QString coinNum = run_script(params);
    params.clear();
    params << SCRIPTS_PATH + "cat_detection.py" << "--image" << img_path <<
              "--cascade" << SCRIPTS_PATH + "haarcascade_frontalcatface.xml";

    coinNum += "(" + run_script(params) + " cats)";
    ui->coins_lbl->setText(coinNum);
}

void MainWindow::on_kernal_slider_valueChanged(int value)
{
    // pass new_value to kernalSize_lbl
    // if value is even increment by 1
    value = (value % 2 == 0) ? value + 1 : value;
    ui->kernalSize_lbl->setText(QString::number(value));
}

void MainWindow::on_detectMetal_btn_clicked()
{
    ui->detectMetal_btn->setEnabled(false);
}

void MainWindow::on_lineFollower_btn_clicked()
{
    QStringList params;

    params << SCRIPTS_PATH + "Line Follower.py";

    QString out = run_script(params);
    qDebug() << out;
}
