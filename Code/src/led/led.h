#include <Arduino.h>
#include "../vars/constants.h"

class Led
{
    private:
    void led_top_on()
    {
        ledcWrite(constants::pins::led::Top_Channel, 255);
    }
    void led_1_on()
    {
        ledcWrite(constants::pins::led::Led1_Channel, 255);
    }
    void led_2_on()
    {
        ledcWrite(constants::pins::led::Led2_Channel, 255);
    }
    void led_top_off()
    {
        ledcWrite(constants::pins::led::Top_Channel, 0);
    }
    void led_1_off()
    {
        ledcWrite(constants::pins::led::Led1_Channel, 0);
    }
    void led_2_off()
    {
        ledcWrite(constants::pins::led::Led2_Channel, 0);
    }
    public:
    uint64_t prev_millis = 0;
    Led()
    {
        ledcSetup(constants::pins::led::Top_Channel, 500, 8);
        ledcSetup(constants::pins::led::Led1_Channel, 500, 8);
        ledcSetup(constants::pins::led::Led2_Channel, 500, 8);
        ledcAttachPin(constants::pins::led::Top, constants::pins::led::Top_Channel);
        ledcAttachPin(constants::pins::led::Led1, constants::pins::led::Led1_Channel);
        ledcAttachPin(constants::pins::led::Led2, constants::pins::led::Led2_Channel);
    }

    void blink()
    {
        Serial.print(millis());
        Serial.println(": LED Blink");
        led_top_on();
        led_1_off();
        led_2_on();
        delay(250);
        led_top_on();
        led_1_on();
        led_2_off();
        delay(250);
        led_top_off();
        led_1_on();
        led_2_on();
        delay(250);
    }
};