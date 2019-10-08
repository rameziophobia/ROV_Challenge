#include "joystick.h"

Joystick::Joystick(QObject *parent) : QObject(parent), velocityPublisher("/rov_velocity", this)
{
    SDL_Init(SDL_INIT_JOYSTICK);

    myJoystick = SDL_JoystickOpen(1);
    if(myJoystick == NULL)
    {
        qDebug() << "No joystick connected";
        exit(1);
    }
    qDebug() << SDL_JoystickNumAxes(myJoystick);
    qDebug() << SDL_JoystickNumButtons(myJoystick);
    //Initiate the publisher and start it, make it of type int
    prevx = 0; prevy = 0; prevz = 0;
    timer = new QTimer();
    timer->setInterval(100);
    timer->start();

    event = new SDL_Event();

    connect(timer,SIGNAL(timeout()),this,SLOT(joystick_update()));
}

void Joystick::joystick_update()
{
    while(SDL_PollEvent(event))
    {
	qDebug() << SDL_JoystickGetAxis(myJoystick,0);
        qDebug() << SDL_JoystickGetAxis(myJoystick,1);
        if(event->type == SDL_JOYAXISMOTION)
        {
            if(event->jaxis.axis == 0)
            {
                if(abs(event->jaxis.value - prevx) > 2150){
                    publishVelocity(SDL_JoystickGetAxis(myJoystick,0), SDL_JoystickGetAxis(myJoystick,1), SDL_JoystickGetAxis(myJoystick,2));
                    prevx = event->jaxis.value;
                }

            }
            else if(event->jaxis.axis == 1)
            {
                if(abs(event->jaxis.value - prevy) > 2150){
                    publishVelocity(SDL_JoystickGetAxis(myJoystick,0), SDL_JoystickGetAxis(myJoystick,1), SDL_JoystickGetAxis(myJoystick,2));
                    prevy = event->jaxis.value;
                }
            }
            else if(event->jaxis.axis == 2)
            {
                if(abs(event->jaxis.value - prevz) > 2150){
                    publishVelocity(SDL_JoystickGetAxis(myJoystick,0), SDL_JoystickGetAxis(myJoystick,1), SDL_JoystickGetAxis(myJoystick,2));
                    prevz = event->jaxis.value;
                }
            }
        }
    }
}

void Joystick::publishVelocity(Sint16 x, Sint16 y, Sint16 z) {
    geometry_msgs::Twist msg;
    msg.linear.x = x;
    msg.linear.y = y;
    msg.linear.z = z;
    velocityPublisher.send(msg);
}
