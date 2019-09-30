#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include "keybindings.h"
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
    void updateTimeLabel(QString newTime);

    void on_switchCameras_clicked();

    void on_startTimer_clicked();

    void on_keyBindings_clicked();

private:
    Ui::MainWindow *ui;
    RovTimer * rovTimer;

    // if feed is unsupported switch to VLCMediaplayer instead of QMediaPlayer https://vlc-qt.tano.si/
    QMediaPlayer *player1;
    QMediaPlayer *player2;

    QVideoWidget *vwmain;
    QVideoWidget *vwsecondary;
    bool switched;
};

#endif // MAINWINDOW_H
