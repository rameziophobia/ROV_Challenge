#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include "keybindings.h"
#include "rovtimer.h"
#include <std_msgs/String.h>
#include "../libs/rospublisher.h"
#include "../libs/rossubscriber.h"
#include "../libs/get_metal_type_client.h"

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
    void updateTimeLabel(QString newTime);

    void on_box1Detect_btn_clicked();
    void on_box2Detect_btn_clicked();
    void on_box3Detect_btn_clicked();
    void on_compareBoxes_btn_clicked();

    void on_startTimer_btn_clicked();
    void on_keyBindings_btn_clicked();
    void on_switchCameras_btn_clicked();

    void on_countCoins_btn_clicked();
    void on_kernal_slider_valueChanged(int value);

    void on_detectMetal_btn_clicked();

    void on_lineFollower_btn_clicked();

private:
    Ui::MainWindow *ui;
    RovTimer * rovTimer;

    // if feed is unsupported switch to VLCMediaplayer instead of QMediaPlayer https://vlc-qt.tano.si/
    QMediaPlayer *player1;
    QMediaPlayer *player2;

    QVideoWidget *vwmain;
    QVideoWidget *vwsecondary;
    bool switched;

    const QString SCRIPTS_PATH = R"(/media/ramez/OS/Ramez/programming/code/Qt/rov_chall_ui/python_scripts/)";
    const QString PYTHON_VERSION = "python3.7";
    void box_script(QString boxNum);
    QString run_script(QStringList);

    RosPublisher<std_msgs::String> boxesPublisher;
    RosSubscriber<std_msgs::String, MainWindow> boxesSubscriber;

    void msgCallback(std_msgs::String msg);

    GetMetalTypeClient metalTypeClient;
    Q_SLOT void metalTypeDetected(QString metalType);
    Q_SLOT void metalDetectionErrorOccurred();
};

#endif // MAINWINDOW_H
