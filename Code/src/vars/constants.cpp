#include "constants.h"
#include <Arduino.h>

//@brief Firmware Version
const char constants::version[] = "v2.0.1";

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


uint8_t constants::pins::motor::FrontLeft_Dir = 4;
uint8_t constants::pins::motor::FrontLeft_Speed = 16;
uint8_t constants::pins::motor::FrontRight_Dir = 17;
uint8_t constants::pins::motor::FrontRight_Speed = 5;
uint8_t constants::pins::motor::BackLeft_Dir = 21;
uint8_t constants::pins::motor::BackLeft_Speed = 3;
uint8_t constants::pins::motor::BackRight_Dir = 33;
uint8_t constants::pins::motor::BackRight_Speed = 22;

uint8_t constants::pins::motor::ServoLowerPin = 12;
uint8_t constants::pins::motor::ServoUpperPin = 14;
uint8_t constants::pins::motor::ServoExtenderPin = 27;

uint8_t constants::pins::motor::ServoExtenderLimitSwitchLower_Pin = 39;
uint8_t constants::pins::motor::ServoExtenderLimitSwitchUpper_Pin = 36;

uint8_t constants::pins::uss::Trigger = 25;
uint8_t constants::pins::uss::Front_Sens = 36;
uint8_t constants::pins::uss::Back_Sens = 39;
uint8_t constants::pins::uss::Left_Sens = 34;
uint8_t constants::pins::uss::Right_Sens = 35;

uint8_t constants::pins::led::LedStrip = 32;

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

    if     (key == "pins::led::Interval")                   { constants::pins::led::Interval = uint8_t_value; }
    else if(key == "pins::led::Top")                        { constants::pins::led::Top = uint8_t_value; }
    else if(key == "pins::led::Led1")                       { constants::pins::led::Led1 = uint8_t_value; }
    else if(key == "pins::led::Led2")                       { constants::pins::led::Led2 = uint8_t_value; }
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