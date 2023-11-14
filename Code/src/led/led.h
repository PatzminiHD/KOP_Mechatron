#include <Arduino.h>
#include "../vars/constants.h"

class led
{
    private:
    void blink_top()
    {
        
    }

    void blink_bottom()
    {

    }
    public:
    uint64_t prev_millis = 0;
    led()
    {
        ledcAttachPin(constants::pins::led::Top, constants::pins::led::Top_Channel);
        ledcAttachPin(constants::pins::led::Led1, constants::pins::led::Led1_Channel);
        ledcAttachPin(constants::pins::led::Led2, constants::pins::led::Led2_Channel);
    }

    void blink()
    {
        blink_top();
        blink_bottom();
    }
};