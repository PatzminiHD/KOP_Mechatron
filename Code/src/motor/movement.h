#include "motor.h"
#include "../vars/constants.h"
#include "../controller/controller.h"
#include "../led/led.h"
#include "../ultrasonic-sensors/sensors.h"
#include "../music/MP3.h"
#include "servoController.h"

#define DIRECTION_FORWARDS  0
#define DIRECTION_RIGHT     90
#define DIRECTION_BACKWARDS 180
#define DIRECTION_LEFT      270

int MP3::VOLUME;
std::string MP3::mp3File;
bool MP3::shouldStop;

class Movement
{
    private:
    Motor Motor_FL;
    Motor Motor_FR;
    Motor Motor_BL;
    Motor Motor_BR;

    Controller controller;
    Led led = Led();
    MP3 mp3 = MP3();
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

        MovementMode = MovementMode_GasBreak;
        DIRECTION = 0;
        SPEED = 0;
        Apply();
        Serial.println("Initialised Motors");
        servoController.init();
        Serial.println("Initialised Servo Controller");
        controller.init();
        Serial.println("Initialised Controller");

        mp3.mp3File = "/test.mp3";
        //MAX VOLUME is 4096
        mp3.VOLUME = MP3_MAX_VOLUME;
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
            //ledcDetachPin(5);
            //ledcSetup(10, 20000, 8);
            //ledcAttachPin(5, 10);
            return 1;
        }

        controller.loop();
        //ledcWrite(10, 128);

        if(controller.konamiCode)
        {
            Serial.println("KONAMI CODE ENTERED!");
            Dance("test");
            controllerButtonSelectPrev = true;  //Stop Mode Switching
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

    void Dance(std::string filename)
    {
        Serial.println("Dance start");

        led.StopBlink();

        if (!SD.exists(("/" + filename + ".txt").c_str()))
        {
            ESP_LOGE("Movement: Dance", "Failed to open file");
            return;
        }

        fs::File file = SD.open(("/" + filename + ".txt").c_str(), FILE_READ);
        char fileLinesTmp[file.size()];
        file.read((uint8_t *)fileLinesTmp, sizeof(fileLinesTmp));
        file.close();
        std::string fileLines = fileLinesTmp;

        mp3.mp3File = ("/" + filename + ".mp3").c_str();
        mp3.Play();

        unsigned long timeStarted = millis(), timeNext = 0;
        uint16_t servoLowerPosPrev = servoController.servoLowerPosition, servoUpperPosPrev = servoController.servoUpperPosition;
        bool led1 = false, led2 = false, ledTop = false, lastLine = false;
        std::string fileLine = "";
        
        DIRECTION = 0;
        SPEED = 0;

        Serial.println("Main dance loop");
        while(!controller.buttonSelect)
        {
            controller.loop();

            if(controller.dPadUp && !controller.dPadUpPrev && mp3.VOLUME + 512 <= MP3_MAX_VOLUME)
            {
                mp3.VOLUME += 512;
                Serial.print("Volume: ");
                Serial.println(mp3.VOLUME);
            }
            else if(controller.dPadDown && !controller.dPadDownPrev && mp3.VOLUME - 512 >= 0)
            {
                mp3.VOLUME -= 512;
                Serial.print("Volume: ");
                Serial.println(mp3.VOLUME);
            }

            if(millis() > timeNext + timeStarted)
            {
                Apply();
                servoController.applyPosition();
                if(led1)
                    Led::led_1_on();
                else
                    Led::led_1_off();
                if(led2)
                    Led::led_2_on();
                else
                    Led::led_2_off();
                if(ledTop)
                    Led::led_top_on();
                else
                    Led::led_top_off();


                if(!lastLine)
                {
                    //fileLine: "timeNext,speed,direction,servoLowerPos,servoUpperPos,led1,led2,ledTop"
                    //          "8951,256,0,90,50,ON,OFF,OFF"
                    
                    fileLine = fileLines.substr(0, fileLines.find('\n'));
                    fileLines = fileLines.substr(fileLines.find('\n') + 1);
                    if(fileLines.find('\n') == fileLines.npos)
                        lastLine = true;

                    timeNext = atoll(fileLine.substr(0, fileLine.find(',')).c_str());

                    Serial.println(fileLine.c_str());
                    
                    fileLine = fileLine.substr(fileLine.find(',') + 1);
                    SPEED = atoi(fileLine.substr(0, fileLine.find(',')).c_str());

                    fileLine = fileLine.substr(fileLine.find(',') + 1);
                    DIRECTION = atoi(fileLine.substr(0, fileLine.find(',')).c_str());

                    fileLine = fileLine.substr(fileLine.find(',') + 1);
                    servoController.servoLowerPosition = atoi(fileLine.substr(0, fileLine.find(',')).c_str());

                    fileLine = fileLine.substr(fileLine.find(',') + 1);
                    servoController.servoUpperPosition = atoi(fileLine.substr(0, fileLine.find(',')).c_str());

                    fileLine = fileLine.substr(fileLine.find(',') + 1);
                    if(fileLine.substr(0, fileLine.find(',')) == "ON")
                        led1 = true;
                    else
                        led1 = false;

                    fileLine = fileLine.substr(fileLine.find(',') + 1);
                    if(fileLine.substr(0, fileLine.find(',')) == "ON")
                        led2 = true;
                    else
                        led2 = false;

                    fileLine = fileLine.substr(fileLine.find(',') + 1);
                    if(fileLine.substr(0, fileLine.find(',')) == "ON")
                        ledTop = true;
                    else
                        ledTop = false;
                }
            }
        }
        servoController.servoLowerPosition = servoLowerPosPrev;
        servoController.servoUpperPosition = servoUpperPosPrev;
        servoController.applyPosition();

        mp3.Stop();
        led.StopBlink();

        Serial.println("End of Dance");
    }
};
