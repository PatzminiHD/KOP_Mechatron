#include <Arduino.h>
#include <string>

#define MAX_MOTOR_SPEED 1023

//@brief Object for motor related tasks
class Motor
{
    private:

    void Apply()
    {
        //Invert Speed because for some reason it seems higher number => lower speed
        SPEED = MAX_MOTOR_SPEED - SPEED;
        ledcWrite(CHANNEL, SPEED);
        SPEED = MAX_MOTOR_SPEED - SPEED;
        digitalWrite(DIR_PIN, DIRECTION);
    }

    public:
    uint8_t DIR_PIN, CHANNEL;
    uint16_t SPEED;
    bool DIRECTION, FORWARD_DIRECTION;

    void SetSpeed(uint16_t speed)
    {
        if(speed > MAX_MOTOR_SPEED)
        {
            SPEED = MAX_MOTOR_SPEED;
        }
        else
        {
            SPEED = speed;
        }
        Apply();
    }

    void Stop()
    {
        SPEED = 0;
        Apply();
    }

    void SetDirection(bool direction)
    {
        if(direction)
        {
            DIRECTION = FORWARD_DIRECTION;
        }
        else
        {
            DIRECTION = !FORWARD_DIRECTION;
        }
        Apply();
    }
};