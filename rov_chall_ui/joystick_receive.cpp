#include "joystick_receive.h"

joystick_receive::joystick_receive()
{
    //initiate receiver, then put received number in received
    received = 0;
    PWM = (float)received / 32768.0 * 255;
    //Send PWM number to hat
}
