#include <Ps3Controller.h>
#include "../vars/constants.h"

class Controller
{   
    private:
    int8_t buttonCirclePrev, buttonXPrev, dPadUpPrev, dPadRightPrev, dPadDownPrev, dPadLeftPrev, buttonStartPrev;
    enum KonamiCodeButtons
    {
        KONAMI_BUTTON_NONE,
        KONAMI_BUTTON_UP,
        KONAMI_BUTTON_DOWN,
        KONAMI_BUTTON_LEFT,
        KONAMI_BUTTON_RIGHT,
        KONAMI_BUTTON_B,
        KONAMI_BUTTON_A,
        KONAMI_BUTTON_START
    };
    KonamiCodeButtons konamiButtonList[11];
    public:
    int8_t joyLX, joyLY, joyRX, joyRY, buttonSelect, buttonStart, buttonSquare, buttonCircle, buttonTriangle, buttonX, dPadUp, dPadRight, dPadDown, dPadLeft, joyRButton, joyLButton, shoulderButtonL, shoulderButtonR;
    ps3_status_battery battery;
    uint8_t throttleGas, throttleBreake;
    unsigned long led_blink_millis;
    bool led_blink, konamiCode, konamiCodePrev;



    void init()
    {
        Ps3.attachOnConnect(OnConnect);
        Ps3.begin(constants::controller_vars::BT_ADDR.c_str());
        for(uint8_t i = 0; i < 11; i++)
        {
            konamiButtonList[i] = KONAMI_BUTTON_NONE;
        }
        konamiCode = false;
        konamiCodePrev = false;
    }

    void loop()
    {
        buttonCirclePrev = buttonCircle;
        buttonXPrev = buttonX;
        dPadUpPrev = dPadUp;
        dPadRightPrev = dPadRight;
        dPadDownPrev = dPadDown;
        dPadLeftPrev = dPadLeft;
        buttonStartPrev = buttonStart;
        konamiCodePrev = konamiCode;


        joyLX = Ps3.data.analog.stick.lx;
        joyLY = Ps3.data.analog.stick.ly;
        joyRX = Ps3.data.analog.stick.rx;
        joyRY = Ps3.data.analog.stick.ry;

        dPadUp    = Ps3.data.button.up;
        dPadRight = Ps3.data.button.right;
        dPadDown  = Ps3.data.button.down;
        dPadLeft  = Ps3.data.button.left;

        joyLButton = Ps3.data.button.l3;
        joyRButton = Ps3.data.button.r3;

        battery = Ps3.data.status.battery;
        
        throttleGas    = Ps3.data.analog.button.l2;
        throttleBreake = Ps3.data.analog.button.r2;

        buttonSelect   = Ps3.data.button.select;
        buttonSquare   = Ps3.data.button.square;
        buttonCircle   = Ps3.data.button.circle;
        buttonTriangle = Ps3.data.button.triangle;

        shoulderButtonL = Ps3.data.button.l1;
        shoulderButtonR = Ps3.data.button.r1;


        if(millis() - led_blink_millis > 250)
        {
            led_blink_millis = millis();
            led_blink = !led_blink;
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

        CheckKonami();
    }

    static void OnConnect()
    {
        Ps3.setRumble(100.0, 250);
        delay(500);
        Ps3.setRumble(100.0, 250);
        delay(500);
        Ps3.setRumble(100.0, 250);
    }

    void CheckKonami()
    {
        for(uint8_t i = 0; i < 10; i++)
        {
            konamiButtonList[i] = konamiButtonList[i+1];
        }

        if(dPadUp && !dPadUpPrev)
            konamiButtonList[10] = KONAMI_BUTTON_UP;
        else if(dPadDown && !dPadDownPrev)
            konamiButtonList[10] = KONAMI_BUTTON_DOWN;
        else if(dPadLeft && !dPadLeftPrev)
            konamiButtonList[10] = KONAMI_BUTTON_LEFT;
        else if(dPadRight && !dPadRightPrev)
            konamiButtonList[10] = KONAMI_BUTTON_RIGHT;
        else if(buttonCircle && !buttonCirclePrev)
            konamiButtonList[10] = KONAMI_BUTTON_B;
        else if(buttonX && !buttonXPrev)
            konamiButtonList[10] = KONAMI_BUTTON_A;
        else if(buttonStart && !buttonStart)
            konamiButtonList[10] = KONAMI_BUTTON_START;

        if(konamiButtonList[10] == KONAMI_BUTTON_START &&
           konamiButtonList[9] == KONAMI_BUTTON_A &&
           konamiButtonList[8] == KONAMI_BUTTON_B &&
           konamiButtonList[7] == KONAMI_BUTTON_RIGHT &&
           konamiButtonList[6] == KONAMI_BUTTON_LEFT &&
           konamiButtonList[5] == KONAMI_BUTTON_RIGHT &&
           konamiButtonList[4] == KONAMI_BUTTON_LEFT &&
           konamiButtonList[3] == KONAMI_BUTTON_DOWN &&
           konamiButtonList[2] == KONAMI_BUTTON_DOWN &&
           konamiButtonList[1] == KONAMI_BUTTON_UP &&
           konamiButtonList[0] == KONAMI_BUTTON_UP &&
           konamiCodePrev == false)
           konamiCode = true;
    }
};