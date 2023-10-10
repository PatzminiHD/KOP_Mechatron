#include <Ps3Controller.h>
#include "../vars/constants.h"

class Controller
{
    public:
    int8_t joyLX, joyLY, joyRX, joyRY;
    ps3_status_battery battery;
    uint8_t throttleGas, throttleBreake;
    unsigned long led_blink_millis;
    bool led_blink;

    void init()
    {
        Ps3.attachOnConnect(OnConnect);
        Ps3.begin(constants::controller_vars::BT_ADDR.c_str());
    }

    void loop()
    {
        joyLX = Ps3.data.analog.stick.lx;
        joyLY = Ps3.data.analog.stick.ly;
        joyRX = Ps3.data.analog.stick.rx;
        joyRY = Ps3.data.analog.stick.ry;

        battery = Ps3.data.status.battery;
        
        throttleGas = Ps3.data.analog.button.l2;
        throttleBreake = Ps3.data.analog.button.r2;

        if(millis() - led_blink_millis > 250)
        {
            led_blink_millis = millis();
            led_blink = !led_blink;
        }
        else
        {
            return;
        }

        switch(Ps3.data.status.battery)
        {
            case ps3_status_battery_full:
                Ps3.setPlayer(10);
                break;
            case ps3_status_battery_high:
                Ps3.setPlayer(9);
                break;
            case ps3_status_battery_low:
                Ps3.setPlayer(7);
                break;
            case ps3_status_battery_dying:
                Ps3.setPlayer(4);
                break;
            case ps3_status_battery_shutdown:
                if(led_blink)
                {
                    Ps3.setPlayer(4);
                }
                else
                {
                    Ps3.setPlayer(1);
                }
                break;
        }
    }

    static void OnConnect()
    {
        Ps3.setRumble(100.0, 250);
        delay(500);
        Ps3.setRumble(100.0, 250);
        delay(500);
        Ps3.setRumble(100.0, 250);
    }
};