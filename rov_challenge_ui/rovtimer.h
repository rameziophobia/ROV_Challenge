#ifndef ROVTIMER_H
#define ROVTIMER_H
#include <QObject>
#include <QTimer>

class RovTimer: public QObject
{
    Q_OBJECT
    Q_PROPERTY(int interval MEMBER m_interval NOTIFY intervalChanged)
    Q_PROPERTY(QString timer_text MEMBER m_label NOTIFY timerChanged)
public:
    RovTimer();
    Q_INVOKABLE QString getTimeText() {
        return m_label;
    }
public slots:
    void start();

signals:
    void intervalChanged(const int &newInt);
    void timerChanged(const QString &newString);

private slots:
    void update();
private:
    QString parseTime(int seconds);

    int m_interval;
    const int START_TIME = 900;
    int time = START_TIME;
    QString m_label = "15:00";
    QTimer * timer;
};

#endif // ROVTIMER_H
