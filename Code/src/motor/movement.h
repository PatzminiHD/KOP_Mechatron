#include "motor.h"
#include "../vars/constants.h"

#define DIRECTION_FORWARDS  0
#define DIRECTION_RIGHT     90
#define DIRECTION_BACKWARDS 180
#define DIRECTION_LEFT      270

class Movement
{
    private:
    Motor Motor_FL = Motor(constants::pins::motor::FrontLeft_Dir,
                           constants::pins::motor::FrontLeft_Speed,
                           0,
                           true);
    Motor Motor_FR = Motor(constants::pins::motor::FrontRight_Dir,
                           constants::pins::motor::FrontRight_Speed,
                           1,
                           true);
    Motor Motor_BL = Motor(constants::pins::motor::BackLeft_Dir,
                           constants::pins::motor::BackLeft_Speed,
                           2,
                           true);
    Motor Motor_BR = Motor(constants::pins::motor::BackRight_Dir,
                           constants::pins::motor::BackRight_Speed,
                           3,
                           true);

    public:
    uint16_t DIRECTION, SPEED;

    void FullSpeed()
    {
        SPEED = MAX_MOTOR_SPEED;
    }

    void Stop()
    {
        SPEED = 0;
    }

    void Forwards()
    {
        DIRECTION = DIRECTION_FORWARDS;
    }
    void Right()
    {
        DIRECTION = DIRECTION_RIGHT;
    }
    void Backwards()
    {
        DIRECTION = DIRECTION_BACKWARDS;
    }
    void Left()
    {
        DIRECTION = DIRECTION_LEFT;
    }

    void Apply()
    {
        double M_FL_Percent, M_FR_Percent, M_BL_Percent, M_BR_Percent, rad;

        if(DIRECTION < 90)
        {
            rad = DIRECTION * DEG_TO_RAD;
            M_FL_Percent = 1.0f;
            M_FR_Percent = cos(rad * 2);
            M_BL_Percent = cos(rad * 2);
            M_BR_Percent = 1.0f;
        }
        else if(DIRECTION < 180)
        {
            rad = (DIRECTION - 90) * DEG_TO_RAD;
            M_FL_Percent = cos(rad * 2);
            M_FR_Percent = -1.0f;
            M_BL_Percent = -1.0f;
            M_BR_Percent = cos(rad * 2);
        }
        else if (DIRECTION < 270)
        {
            rad = (DIRECTION - 90) * DEG_TO_RAD;
            M_FL_Percent = -1.0f;
            M_FR_Percent = cos(rad * 2);
            M_BL_Percent = cos(rad * 2);
            M_BR_Percent = -1.0f;
        }
        else if (DIRECTION < 360)
        {
            rad = (DIRECTION - 180) * DEG_TO_RAD;
            M_FL_Percent = cos(rad * 2);
            M_FR_Percent = +1,0;
            M_BL_Percent = +1.0;
            M_BR_Percent = cos(rad * 2);
        }
    }
};