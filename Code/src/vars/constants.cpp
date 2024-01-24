#include "constants.h"
#include <Arduino.h>

//@brief Firmware Version
const char constants::version[] = "v1.0.0";


//@brief MCP3008 Chip Select Pin
uint8_t constants::pins::mcp3008_cs = 17;

//@brief SC-Card Chip Select Pin
uint8_t constants::pins::sdcard_cs = 5;

//@brief The path of the config file
const char constants::sdcardIO::ConfigFilePath[] = "/config.txt";


//@brief The Interval of the blinking in ms
uint16_t constants::pins::led::Interval = 500;

//@brief The Interval of the blinking in ms
uint16_t constants::pins::led::BottomLEDsIntervalOn = 500;

//@brief The Interval of the blinking in ms
uint16_t constants::pins::led::BottomLEDsIntervalOff = 500;

//@brief The Interval of the blinking in ms
uint16_t constants::pins::led::BottomLEDsIntervalBetween = 750;

//@brief Pin of the big Top LEDs, has to be a PWM Pin
uint8_t constants::pins::led::Top = 13;

//@brief Pin of one half of the body LEDs, has to be a PWM Pin
uint8_t constants::pins::led::Led1 = 15;

//@brief Pin of the other half of the body LEDs, has to be a PWM Pin
uint8_t constants::pins::led::Led2 = 2;

//@brief ledc Channel for the big Top LED
uint8_t constants::pins::led::Top_Channel = 4;

//@brief ledc Channel for one half of the body LEDs
uint8_t constants::pins::led::Led1_Channel = 5;

//@brief ledc Channel for the other half of the body LEDs
uint8_t constants::pins::led::Led2_Channel = 6;


uint8_t constants::pins::motor::FrontLeft_Dir = 4;
uint8_t constants::pins::motor::FrontLeft_Speed = 16;
uint8_t constants::pins::motor::FrontRight_Dir = 17;
uint8_t constants::pins::motor::FrontRight_Speed = 5;
uint8_t constants::pins::motor::BackLeft_Dir = 21;
uint8_t constants::pins::motor::BackLeft_Speed = 3;
uint8_t constants::pins::motor::BackRight_Dir = 1;
uint8_t constants::pins::motor::BackRight_Speed = 22;

//@brief The Buzzer Pin
uint8_t constants::pins::buzzer::buzzer_pin = 5;
uint8_t constants::pins::buzzer::pwm_channel = 7;

uint8_t constants::pins::uss::Trigger = 25;
uint8_t constants::pins::uss::Front_Sens = 36;
uint8_t constants::pins::uss::FrontLeft_Sens = 39;
uint8_t constants::pins::uss::BackLeft_Sens = 34;
uint8_t constants::pins::uss::Back_Sens = 35;
uint8_t constants::pins::uss::BackRight_Sens = 32;
uint8_t constants::pins::uss::FrontRight_Sens = 33;

uint8_t constants::uss::FrontBack_Min_Distance = 15;
uint8_t constants::uss::Side_Min_Distance = 20;


std::string constants::controller_vars::BT_ADDR = "8C:7C:B5:5F:3B:64";

//@brief Set the value of a setting based on the name
//@param key The name of the setting
//@param value The value the setting should be set to
//@return 0 if setting was successful
//@return 1 if setting name was not found
bool constants::setValue(std::string key, String value)
{
    uint8_t uint8_t_value = atoi(value.c_str());
    
    String tmp_value = value;
    uint8_t ip_0, ip_1, ip_2, ip_3;
    ip_0 = atoi(tmp_value.substring(0, tmp_value.indexOf(".")).c_str());
    tmp_value = tmp_value.substring(tmp_value.indexOf(".") + 1);
    ip_1 = atoi(tmp_value.substring(0, tmp_value.indexOf(".")).c_str());
    tmp_value = tmp_value.substring(tmp_value.indexOf(".") + 1);
    ip_2 = atoi(tmp_value.substring(0, tmp_value.indexOf(".")).c_str());
    tmp_value = tmp_value.substring(tmp_value.indexOf(".") + 1);
    ip_3 = atoi(tmp_value.substring(0, tmp_value.indexOf(".")).c_str());
    
    IPAddress ipaddress_value = IPAddress(ip_0, ip_1, ip_2, ip_3);

    if     (key == "pins::mcp3008_cs")                      { constants::pins::mcp3008_cs = uint8_t_value; }
    else if(key == "pins::led::Interval")                   { constants::pins::led::Interval = uint8_t_value; }
    else if(key == "pins::led::Top")                        { constants::pins::led::Top = uint8_t_value; }
    else if(key == "pins::led::Led1")                       { constants::pins::led::Led1 = uint8_t_value; }
    else if(key == "pins::led::Led2")                       { constants::pins::led::Led2 = uint8_t_value; }
    else if(key == "pins::led::Top_Channel")                { constants::pins::led::Top_Channel = uint8_t_value; }
    else if(key == "pins::led::Led1_Channel")               { constants::pins::led::Led1_Channel = uint8_t_value; }
    else if(key == "pins::led::Led2_Channel")               { constants::pins::led::Led2_Channel = uint8_t_value; }
    else if(key == "pins::motor::FrontLeft_Dir")            { constants::pins::motor::FrontLeft_Dir = uint8_t_value; }
    else if(key == "pins::motor::FrontLeft_Speed")          { constants::pins::motor::FrontLeft_Speed = uint8_t_value; }
    else if(key == "pins::motor::FrontRight_Dir")           { constants::pins::motor::FrontRight_Dir = uint8_t_value; }
    else if(key == "pins::motor::FrontRight_Speed")         { constants::pins::motor::FrontRight_Speed = uint8_t_value; }
    else if(key == "pins::motor::BackLeft_Dir")             { constants::pins::motor::BackLeft_Dir = uint8_t_value; }
    else if(key == "pins::motor::BackLeft_Speed")           { constants::pins::motor::BackLeft_Speed = uint8_t_value; }
    else if(key == "pins::motor::BackRight_Dir")            { constants::pins::motor::BackRight_Dir = uint8_t_value; }
    else if(key == "pins::motor::BackRight_Speed")          { constants::pins::motor::BackRight_Speed = uint8_t_value; }
    else { return false; }
    return true;
}