#ifndef ROVTIMER_H
#define ROVTIMER_H
#include <QObject>
#include <QTimer>

class RovTimer: public QObject
{
    Q_OBJECT
    Q_PROPERTY(int interval MEMBER m_interval NOTIFY intervalChanged)
public:
    RovTimer();
public slots:
    void start();

signals:
    void intervalChanged(const int &newInt);

private slots:
    void update();
private:
    int m_interval;
    QTimer * timer;
};

#endif // ROVTIMER_H
