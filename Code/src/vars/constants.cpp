#include "constants.h"
#include <Arduino.h>

//@brief Firmware Version
const char constants::version[] = "v0.2.0";


//@brief MCP3008 Chip Select Pin
uint8_t constants::pins::mcp3008_cs = 17;


//@brief The Frequency of the PWM signal
uint16_t constants::pins::led::Frequency = 500;

//@brief Red Pin of the RGB LED, has to be a PWM Pin
uint8_t constants::pins::led::Red = 15;

//@brief Green Pin of the RGB LED, has to be a PWM Pin
uint8_t constants::pins::led::Green = 2;

//@brief Blue Pin of the RGB LED, has to be a PWM Pin
uint8_t constants::pins::led::Blue = 4;

//@brief ledc Channel for the Red Pin of the RGB LED
uint8_t constants::pins::led::Red_Channel = 0;

//@brief ledc Channel for the Green Pin of the RGB LED
uint8_t constants::pins::led::Green_Channel = 1;

//@brief ledc Channel for the Blue Pin of the RGB LED
uint8_t constants::pins::led::Blue_Channel = 2;


uint8_t constants::pins::motor::FrontLeft_Dir = 14;
uint8_t constants::pins::motor::FrontLeft_Speed = 27;
uint8_t constants::pins::motor::FrontRight_Dir = 13;
uint8_t constants::pins::motor::FrontRight_Speed = 12;
uint8_t constants::pins::motor::BackLeft_Dir = 26;
uint8_t constants::pins::motor::BackLeft_Speed = 25;
uint8_t constants::pins::motor::BackRight_Dir = 33;
uint8_t constants::pins::motor::BackRight_Speed = 32;


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
    else if(key == "pins::led::Frequency")                  { constants::pins::led::Frequency = uint8_t_value; }
    else if(key == "pins::led::Red")                        { constants::pins::led::Red = uint8_t_value; }
    else if(key == "pins::led::Green")                      { constants::pins::led::Green = uint8_t_value; }
    else if(key == "pins::led::Blue")                       { constants::pins::led::Blue = uint8_t_value; }
    else if(key == "pins::led::Red_Channel")                { constants::pins::led::Red_Channel = uint8_t_value; }
    else if(key == "pins::led::Green_Channel")              { constants::pins::led::Green_Channel = uint8_t_value; }
    else if(key == "pins::led::Blue_Channel")               { constants::pins::led::Blue_Channel = uint8_t_value; }
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