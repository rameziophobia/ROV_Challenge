#ifndef JOYSTIC_RECEIVE_H
#define JOYSTIC_RECEIVE_H

#include <QObject>

class Joystic_receive
{
private:
    //ROS receiver
    int received;
    int PWM;
public:
    Joystic_receive();
};

#endif // JOYSTIC_RECEIVE_H
