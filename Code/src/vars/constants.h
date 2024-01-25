#ifndef CONSTANTS_CLASS
#define CONSTANTS_CLASS

#include <string>
#include <IPAddress.h>


 //@brief Contains all Constants for the firmware. Change them in constants.cpp
class constants
{
    public:
    static const char version[];

    //@brief All custom Pins
    class pins
    {
        public:
        
        class led
        {
            public:
            static uint16_t Interval;
            static uint16_t BottomLEDsIntervalOff;
            static uint16_t BottomLEDsIntervalOn;
            static uint16_t BottomLEDsIntervalBetween;
            static uint8_t Top;
            static uint8_t Led1;
            static uint8_t Led2;
            static uint8_t Top_Channel;
            static uint8_t Led1_Channel;
            static uint8_t Led2_Channel;
        };

        class motor
        {
            public:
            static uint8_t FrontLeft_Dir;
            static uint8_t FrontLeft_Speed;
            static uint8_t FrontRight_Dir;
            static uint8_t FrontRight_Speed;
            static uint8_t BackLeft_Dir;
            static uint8_t BackLeft_Speed;
            static uint8_t BackRight_Dir;
            static uint8_t BackRight_Speed;

            static uint8_t ServoLowerPin;
            static uint8_t ServoUpperPin;
            static uint8_t ServoExtenderPin;

            static uint8_t ServoExtenderLimitSwitchUpper_Pin;
            static uint8_t ServoExtenderLimitSwitchLower_Pin;
        };

        class buzzer
        {
            public:
            static uint8_t buzzer_pin;
            static uint8_t pwm_channel;
        };
        class uss
        {
            public:
            static uint8_t Trigger;
            static uint8_t Front_Sens;
            static uint8_t FrontLeft_Sens;
            static uint8_t BackLeft_Sens;
            static uint8_t Back_Sens;
            static uint8_t BackRight_Sens;
            static uint8_t FrontRight_Sens;
        };
    };

    class uss
    {
        public:
        static uint8_t FrontBack_Min_Distance;
        static uint8_t Side_Min_Distance;
    };

    class sdcardIO
    {
        public:
        static const char ConfigFilePath[];
    };

    class controller_vars
    {
        public:
        static std::string BT_ADDR;
    };

    static bool setValue(std::string, String);
};

#endif