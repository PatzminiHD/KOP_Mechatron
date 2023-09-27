#include "motor.h"
#include "../vars/constants.h"

#define DIRECTION_FORWARDS  0
#define DIRECTION_RIGHT     90
#define DIRECTION_BACKWARDS 180
#define DIRECTION_LEFT      270

class Movement
{
    private:

    Motor Motor_FL;
    Motor Motor_FR;
    Motor Motor_BL;
    Motor Motor_BR;

    public:
    uint16_t DIRECTION, SPEED;

    void init()
    {
        Motor_FL.CHANNEL = 0;
        Motor_FL.DIR_PIN = constants::pins::motor::FrontLeft_Dir;
        Motor_FL.FORWARD_DIRECTION = false;
        pinMode(constants::pins::motor::FrontLeft_Dir, OUTPUT);
        pinMode(constants::pins::motor::FrontLeft_Speed, OUTPUT);
        ledcSetup(0, 20000, 10);
        ledcAttachPin(constants::pins::motor::FrontLeft_Speed, 0);

        Motor_FR.CHANNEL = 1;
        Motor_FR.DIR_PIN = constants::pins::motor::FrontRight_Dir;
        Motor_FR.FORWARD_DIRECTION = true;
        pinMode(constants::pins::motor::FrontRight_Dir, OUTPUT);
        pinMode(constants::pins::motor::FrontRight_Speed, OUTPUT);
        ledcSetup(1, 20000, 10);
        ledcAttachPin(constants::pins::motor::FrontRight_Speed, 1);

        Motor_BL.CHANNEL = 2;
        Motor_BL.DIR_PIN = constants::pins::motor::BackLeft_Dir;
        Motor_BL.FORWARD_DIRECTION = false;
        pinMode(constants::pins::motor::BackLeft_Dir, OUTPUT);
        pinMode(constants::pins::motor::BackLeft_Speed, OUTPUT);
        ledcSetup(2, 20000, 10);
        ledcAttachPin(constants::pins::motor::BackLeft_Speed, 2);

        Motor_BR.CHANNEL = 3;
        Motor_BR.DIR_PIN = constants::pins::motor::BackRight_Dir;
        Motor_BR.FORWARD_DIRECTION = true;
        pinMode(constants::pins::motor::BackRight_Dir, OUTPUT);
        pinMode(constants::pins::motor::BackRight_Speed, OUTPUT);
        ledcSetup(3, 20000, 10);
        ledcAttachPin(constants::pins::motor::BackRight_Speed, 3);
    }

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

        if(M_FL_Percent < 0)
        {
            Motor_FL.SetDirection(false);
        }
        else
        {
            Motor_FL.SetDirection(true);
        }

        if(M_FR_Percent < 0)
        {
            Motor_FR.SetDirection(false);
        }
        else
        {
            Motor_FR.SetDirection(true);
        }

        if(M_BL_Percent < 0)
        {
            Motor_BL.SetDirection(false);
        }
        else
        {
            Motor_BL.SetDirection(true);
        }

        if(M_BR_Percent < 0)
        {
            Motor_BR.SetDirection(false);
        }
        else
        {
            Motor_BR.SetDirection(true);
        }

        Motor_FL.SetSpeed(map(abs(M_FL_Percent) * 100.0, 0, 100, 0, SPEED));
        Motor_FR.SetSpeed(map(abs(M_FR_Percent) * 100.0, 0, 100, 0, SPEED));
        Motor_BL.SetSpeed(map(abs(M_BL_Percent) * 100.0, 0, 100, 0, SPEED));
        Motor_BR.SetSpeed(map(abs(M_BR_Percent) * 100.0, 0, 100, 0, SPEED));
    }
};