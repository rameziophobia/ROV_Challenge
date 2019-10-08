#ifndef JOYSTICK_RECEIVE_H
#define JOYSTICK_RECEIVE_H

#include <QObject>
#include "QDebug"

class Joystick_receive
{
private:
    //ROS receiver
    float x;
    float y;
    float z;
    float r;
    int PWMTR;
    int PWMTL;
    int PWMBR;
    int PWMBL;
    int PWMT;
    int PWMB;
public:
    Joystick_receive();
    float maxVal(float a,float b);
    float minVal(float a,float b);
};

#endif // JOYSTICK_RECEIVE_H
