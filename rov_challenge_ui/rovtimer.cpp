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

void RovTimer::update()
{
    qDebug() << "updating...";
}
