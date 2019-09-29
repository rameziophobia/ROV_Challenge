#include "rovtimer.h"
#include <QTimer>
#include <QDebug>

RovTimer::RovTimer()
{
    timer = new QTimer();
//    timer->start(m_interval);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
}

void RovTimer::start()
{
    timer->start(m_interval);
}

QString RovTimer::parseTime(int time)
{
    QString minutes = QString::number(time / 60);
    QString seconds = QString::number(time % 60);

    if(seconds.length() < 2){
        seconds = "0" + seconds;
    }
    return minutes + ":" + seconds;
}

void RovTimer::update()
{
    time--;
    m_label = parseTime(time);
    qDebug() << "updating1... " << m_label;
    emit timeChanged(m_label);

}
