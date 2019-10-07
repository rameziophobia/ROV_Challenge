#ifndef JOYSTICK_RECEIVE_H
#define JOYSTICK_RECEIVE_H


class joystick_receive
{
private:
    //ROS receiver
    int receivedx;
    int receivedy;
    int receivedz;
    int receivedr;
    int PWMTR;
    int PWMTL;
    int PWMBR;
    int PWMBL;
    int PWMT;
    int PWMB;
public:
    joystick_receive();
};

#endif // JOYSTICK_RECEIVE_H
