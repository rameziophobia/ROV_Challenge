#ifndef ROVTIMER_H
#define ROVTIMER_H
#include <QObject>
#include <QTimer>

class RovTimer: public QObject
{
    Q_OBJECT

public:
    RovTimer();
    Q_INVOKABLE QString getTimeText() {
        return m_label;
    }

signals:
    void timeChanged(QString newTime);

public slots:
    void start();

private slots:
    void update();

private:
    QString parseTime(int seconds);
    int m_interval = 1000;
    const int START_TIME = 900;
    int time = START_TIME;
    QString m_label = "15:00";
    QTimer * timer;
};

#endif // ROVTIMER_H
