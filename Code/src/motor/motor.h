#include <Arduino.h>
#include <string>

#define MAX_MOTOR_SPEED 1023

//@brief Object for motor related tasks
class Motor
{
    private:
    uint8_t DIR_PIN, CHANNEL;
    uint16_t SPEED;
    bool DIRECTION, FORWARD_DIRECTION;

    void Apply()
    {
        ledcWrite(CHANNEL, SPEED);
        digitalWrite(DIR_PIN, DIRECTION);
    }

    public:
    Motor(uint8_t dirPin, uint8_t speedPin, uint8_t channel, bool forwardDirection)
    {
        DIR_PIN = dirPin;
        CHANNEL = channel;
        SPEED = 0;
        FORWARD_DIRECTION = forwardDirection;
        pinMode(dirPin, OUTPUT);
        pinMode(speedPin, OUTPUT);
        ledcSetup(channel, 20000, 10);
        ledcAttachPin(speedPin, channel);
        Apply();
    }

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