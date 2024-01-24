#include "motor.h"
#include "../vars/constants.h"
#include "../controller/controller.h"
#include "../music/buzzer.h"
#include "../led/led.h"
#include "../ultrasonic-sensors/sensors.h"

#define DIRECTION_FORWARDS  0
#define DIRECTION_RIGHT     90
#define DIRECTION_BACKWARDS 180
#define DIRECTION_LEFT      270

class Movement
{
    private:
    Buzzer buzzer;

    Motor Motor_FL;
    Motor Motor_FR;
    Motor Motor_BL;
    Motor Motor_BR;

    enum MovementModeEnum
    {
        MovementMode_JoyLeft,
        MovementMode_GasBreak,
        MovementMode_LAST,
    };

    public:
    Controller controller;
    Led led = Led();
    Sensors sensors = Sensors();
    uint16_t DIRECTION, SPEED;
    uint8_t MovementMode;
    bool controllerButtonSelectPrev = false;

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

        controller.init();
        buzzer.init();

        MovementMode = MovementMode_GasBreak;
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

    void TurnLeft()
    {
        Motor_FL.SetDirection(false);
        Motor_BL.SetDirection(false);
        Motor_FR.SetDirection(true);
        Motor_BR.SetDirection(true);

        Motor_FL.SetSpeed(SPEED);
        Motor_BL.SetSpeed(SPEED);
        Motor_FR.SetSpeed(SPEED);
        Motor_BR.SetSpeed(SPEED);
    }

    void TurnRight()
    {
        Motor_FL.SetDirection(true);
        Motor_BL.SetDirection(true);
        Motor_FR.SetDirection(false);
        Motor_BR.SetDirection(false);

        Motor_FL.SetSpeed(SPEED);
        Motor_BL.SetSpeed(SPEED);
        Motor_FR.SetSpeed(SPEED);
        Motor_BR.SetSpeed(SPEED);
    }

    uint8_t HandleControllerInputs()
    {
        if(!Ps3.isConnected())
        {
            DIRECTION = 0;
            SPEED = 0;
            Apply();
            return 1;
        }

        controller.loop();

        if(controller.buttonSelect == 1 && controllerButtonSelectPrev == false)
        {
            MovementMode++;
            if(MovementMode >= MovementMode_LAST)
            {
                MovementMode = 0;
            }
        }
        controllerButtonSelectPrev = controller.buttonSelect == 1;
        if(controller.buttonSquare == 1)
        {
            Serial.println(sensors.CanGoFront());
        }
        switch(MovementMode)
        {
            case MovementMode_JoyLeft:
                HandleMovementModeJoyLeft();
                break;

            case MovementMode_GasBreak:
                HandleMovementModeGasBreak();
                break;

            default:
                return 2;
        }

        return 0;
    }

    void HandleMovementModeGasBreak()
    {
        if(controller.joyLX < -10 || controller.joyLX > 10)
        {
            SPEED = map(abs(controller.joyLX), 0, 128, 0, MAX_MOTOR_SPEED);
            if(controller.joyLX < 0)
            {
                TurnLeft();
            }
            else
            {
                TurnRight();
            }
            return;
        }

        SPEED = map(abs(controller.throttleGas - controller.throttleBreake), 0, 128, 0, MAX_MOTOR_SPEED);
        
        if(controller.throttleGas - controller.throttleBreake > 0)
        {
            DIRECTION = 180;
        }
        else
        {
            DIRECTION = 0;
        }

        Apply();
    }

    void HandleMovementModeJoyLeft()
    {
        if(controller.joyLX != 0)
        {
            float tmp = atan(float(controller.joyLY) / float(controller.joyLX));
            DIRECTION = tmp * RAD_TO_DEG + 90;

            if(controller.joyLX < 0)
            {
            DIRECTION += 180;
            }
        }
        else
        {
            DIRECTION = 0;
        }
        SPEED = map(sqrt(controller.joyLY*controller.joyLY + controller.joyLX*controller.joyLX), 0, 128, 0, MAX_MOTOR_SPEED);
        Apply();
    }
};