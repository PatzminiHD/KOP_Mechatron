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
        static uint8_t mcp3008_cs;

        class led
        {
            public:
            static uint16_t Frequency;
            static uint8_t Red;
            static uint8_t Green;
            static uint8_t Blue;
            static uint8_t Red_Channel;
            static uint8_t Green_Channel;
            static uint8_t Blue_Channel;
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
        };
    };

    class controller_vars
    {
        public:
        static std::string BT_ADDR;
    };

    static bool setValue(std::string, String);
};

#endif