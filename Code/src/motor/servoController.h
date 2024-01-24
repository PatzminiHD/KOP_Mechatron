#include <Servo.h>
#include "../vars/constants.h"

#define SERVO_UPPER_HOMING_POSITION 20
#define SERVO_UPPER_HOME_POSITION 0
#define SERVO_LOWER_HOME_POSITION 90
#define SERVO_HOMING_SPEED 11           //Lower Value -> higher Speed

//@brief Object of servo
class ServoController
{
    private:
    Servo servoLower;
    Servo servoUpper;
    Servo servoExtender;
    uint8_t servoLowerPosition = 90;
    uint8_t servoUpperPosition = 0;

    public:
    void init()
    {
        pinMode(constants::pins::motor::ServoLowerPin, OUTPUT);
        pinMode(constants::pins::motor::ServoUpperPin, OUTPUT);
        pinMode(constants::pins::motor::ServoExtenderPin, OUTPUT);
        pinMode(constants::pins::motor::ServoExtenderLimitSwitchUpper_Pin, INPUT);
        pinMode(constants::pins::motor::ServoExtenderLimitSwitchLower_Pin, INPUT);
        servoLower.attach(constants::pins::motor::ServoLowerPin, 4, 0, 180);
        servoUpper.attach(constants::pins::motor::ServoUpperPin, 5, 0, 180);
        servoExtender.attach(constants::pins::motor::ServoExtenderPin, 6, 0, 180);

        resetPosition();
        homePosition();
    }

    void applyPosition()
    {
        servoLower.write(servoLowerPosition);
        servoUpper.write(servoUpperPosition);
    }

    void moveServoUpper(int8_t dirAndSpeed)
    {
        int16_t mapped = dirAndSpeed / 25;
        if(servoUpperPosition + mapped > 180)
        {
            servoUpperPosition = 180;
            return;
        }
        if(servoUpperPosition + mapped < 0)
        {
            servoUpperPosition = 0;
            return;
        }
        servoUpperPosition = servoUpperPosition + mapped;
    }

    void moveServoLower(int8_t dirAndSpeed)
    {
        int16_t mapped = dirAndSpeed / 25;
        if(servoLowerPosition + mapped > 180)
        {
            servoLowerPosition = 180;
            return;
        }
        if(servoLowerPosition + mapped < 0)
        {
            servoLowerPosition = 0;
            return;
        }
        servoLowerPosition = servoLowerPosition + mapped;
    }

    void resetPosition()
    {
        fullyRetractExtender();
        servoLowerPosition = 90;
        servoUpperPosition = SERVO_UPPER_HOMING_POSITION;
        applyPosition();
    }

    void homePosition()
    {
        fullyRetractExtender();

        //Set Upper Servo to Homing Position 
        for (uint8_t i = servoUpperPosition; i != SERVO_UPPER_HOMING_POSITION;)
        {
            servoUpperPosition = i;
            applyPosition();
            if(i > SERVO_UPPER_HOMING_POSITION)
                i--;
            else
                i++;
            
            delay(SERVO_HOMING_SPEED);
        }

        //Home Lower Servo
        for (uint8_t i = servoLowerPosition; i != SERVO_LOWER_HOME_POSITION;)
        {
            servoLowerPosition = i;
            applyPosition();
            if(i > SERVO_LOWER_HOME_POSITION)
                i--;
            else
                i++;
            delay(SERVO_HOMING_SPEED);
        }

        //Home Upper Servo
        for (uint8_t i = servoUpperPosition; i != SERVO_UPPER_HOME_POSITION;)
        {
            servoUpperPosition = i;
            applyPosition();
            if(i > SERVO_UPPER_HOME_POSITION)
                i--;
            else
                i++;
            delay(SERVO_HOMING_SPEED);
        }
    }

    void fullyExtendExtender()
    {
        while(extendExtender());
    }

    bool extendExtender()
    {
        if(!digitalRead(constants::pins::motor::ServoExtenderLimitSwitchUpper_Pin))
        {
            Serial.print(millis());
            Serial.println("  Servo Extender Extend...");
            servoExtender.write(40);
            delay(3);
            servoExtender.write(90);
        }
        if(digitalRead(constants::pins::motor::ServoExtenderLimitSwitchUpper_Pin))
        {
            servoExtender.write(100);
            while(digitalRead(constants::pins::motor::ServoExtenderLimitSwitchUpper_Pin))
            {
                ;
            }
            delay(1);
            servoExtender.write(90);
            return false;
        }
        return true;
    }

    void fullyRetractExtender()
    {
        while(retractExtender());
    }

    bool retractExtender()
    {
        if(!digitalRead(constants::pins::motor::ServoExtenderLimitSwitchLower_Pin))
        {
            Serial.print(millis());
            Serial.println("  Servo Extender Retract...");
            servoExtender.write(140);
            delay(3);
            servoExtender.write(90);
        }
        if(digitalRead(constants::pins::motor::ServoExtenderLimitSwitchLower_Pin))
        {
            servoExtender.write(80);
            while(digitalRead(constants::pins::motor::ServoExtenderLimitSwitchLower_Pin))
            {
                ;
            }
            delay(1);
            servoExtender.write(90);
            return false;
        }
        return true;
    }
};