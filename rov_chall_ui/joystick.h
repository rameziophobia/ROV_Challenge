#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <QObject>
#include "SDL2/SDL.h"
#include "SDL2/SDL_joystick.h"
#include "QDebug"
#include "QThread"
#include <QTimer>

class Joystick : public QObject
{
    Q_OBJECT

private:
    SDL_Joystick *myJoystick;
    QTimer * timer;
    SDL_Event *event;
    int prevx, prevy, prevz;
    //Publisher
public:
    explicit Joystick(QObject *parent = nullptr);

public slots:
    void joystick_update();

signals:

public slots:
};

#endif // JOYSTICK_H
