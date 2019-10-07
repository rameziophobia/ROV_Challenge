#include "joystick.h"

Joystick::Joystick(QObject *parent) : QObject(parent)
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
                if(abs(event->jaxis.value - prevx) > 300){
                    //Send SDL_JoystickGetAxis(myJoystick,0) + SDL_JoystickGetAxis(myJoystick,1) + SDL_JoystickGetAxis(myJoystick,2) to PI using a topic
                    prevx = event->jaxis.value;
                }

            }
            else if(event->jaxis.axis == 1)
            {
                if(abs(event->jaxis.value - prevy) > 300){
                    //Send SDL_JoystickGetAxis(myJoystick,0) + SDL_JoystickGetAxis(myJoystick,1) + SDL_JoystickGetAxis(myJoystick,2) to PI using a topic
                    prevy = event->jaxis.value;
                }
            }
            else if(event->jaxis.axis == 2)
            {
                if(abs(event->jaxis.value - prevz) > 300){
                    //Send SDL_JoystickGetAxis(myJoystick,0) + SDL_JoystickGetAxis(myJoystick,1) + SDL_JoystickGetAxis(myJoystick,2) to PI using a topic
                    prevz = event->jaxis.value;
                }
            }
        }
    }
}
