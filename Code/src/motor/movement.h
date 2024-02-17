#include "motor.h"
#include "../vars/constants.h"
#include "../controller/controller.h"
#include "../music/buzzer.h"
#include "../led/led.h"
#include "../ultrasonic-sensors/sensors.h"
#include "servoController.h"

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

    Controller controller;
    Led led = Led();
    Sensors sensors = Sensors();

    ServoController servoController;

    enum MovementModeEnum
    {
        MovementMode_JoyLeft,
        MovementMode_GasBreak,
        MovementMode_LAST,
    };

    public:
    uint16_t DIRECTION, SPEED;
    uint8_t MovementMode;
    bool controllerButtonSelectPrev = false, controllerButtonCirclePrev = false;

    void init()
    {
        servoController.init();

        Motor_FL.CHANNEL = 0;
        Motor_FL.DIR_PIN = constants::pins::motor::FrontLeft_Dir;
        Motor_FL.SPEED_PIN = constants::pins::motor::FrontLeft_Speed;
        Motor_FL.FORWARD_DIRECTION = false;
        Motor_FL.init();

        Motor_FR.CHANNEL = 1;
        Motor_FR.DIR_PIN = constants::pins::motor::FrontRight_Dir;
        Motor_FR.SPEED_PIN = constants::pins::motor::FrontRight_Speed;
        Motor_FR.FORWARD_DIRECTION = true;
        Motor_FR.init();

        Motor_BL.CHANNEL = 2;
        Motor_BL.DIR_PIN = constants::pins::motor::BackLeft_Dir;
        Motor_BL.SPEED_PIN = constants::pins::motor::BackLeft_Speed;
        Motor_BL.FORWARD_DIRECTION = false;
        Motor_BL.init();

        Motor_BR.CHANNEL = 3;
        Motor_BR.DIR_PIN = constants::pins::motor::BackRight_Dir;
        Motor_BR.SPEED_PIN = constants::pins::motor::BackRight_Speed;
        Motor_BR.FORWARD_DIRECTION = true;
        Motor_BR.init();

        controller.init();

        MovementMode = MovementMode_GasBreak;

        DIRECTION = 0;
        SPEED = 0;
        Apply();
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

        if(controller.konamiCode)
        {
            Serial.println("KONAMI CODE ENTERED!");
        }

        if(controller.buttonSelect == 1 && controllerButtonSelectPrev == false)
        {
            MovementMode++;
            if(MovementMode >= MovementMode_LAST)
            {
                MovementMode = 0;
            }
        }

        if(controller.dPadLeft)
            servoController.turnServoLowerCW();
        else if(controller.dPadRight)
            servoController.turnServoLowerCCW();

        if(controller.dPadUp)
            servoController.turnServoUpperCCW();
        else if(controller.dPadDown)
            servoController.turnServoUpperCW();

        if(controller.shoulderButtonL)
            servoController.retractExtender();
        else if(controller.shoulderButtonR)
            servoController.extendExtender();

        servoController.applyPosition();


        controllerButtonSelectPrev = controller.buttonSelect == 1;
        if(controller.buttonSquare == 1)
        {
            //Serial.println(sensors.CanGoFront());
        }
        if(controller.buttonCircle == 1 && controllerButtonCirclePrev == 0)
        {
            led.Toggle();
        }
        controllerButtonCirclePrev = controller.buttonCircle == 1;
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
        if(controller.joyRX < -10 || controller.joyRX > 10)
        {
            SPEED = map(abs(controller.joyRX), 0, 128, 0, MAX_MOTOR_SPEED);
            if(controller.joyRX < 0)
            {
                TurnLeft();
            }
            else
            {
                TurnRight();
            }
            return;
        }

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