#include <Arduino.h>
#include "../vars/constants.h"

#define LED_BLINK_DELAY 100

class Led
{
    private:
    TaskHandle_t blinkLEDsTask = NULL;

    static void BlinkLEDsTask(void * parameter)
    {
        bool topLedFlag = false;
        while(!false)
        {
            led_1_on();
            vTaskDelay(LED_BLINK_DELAY / portTICK_PERIOD_MS);
            if(topLedFlag)
                led_top_on();
            led_1_off();
            vTaskDelay(LED_BLINK_DELAY / portTICK_PERIOD_MS);
            led_1_on();
            vTaskDelay(LED_BLINK_DELAY / portTICK_PERIOD_MS);
            if(topLedFlag)
                led_top_off();
            led_1_off();

            vTaskDelay((LED_BLINK_DELAY * 2) / portTICK_PERIOD_MS);
            
            led_2_on();
            vTaskDelay(LED_BLINK_DELAY / portTICK_PERIOD_MS);
            if(!topLedFlag)
                led_top_on();
            led_2_off();
            vTaskDelay(LED_BLINK_DELAY / portTICK_PERIOD_MS);
            led_2_on();
            vTaskDelay(LED_BLINK_DELAY / portTICK_PERIOD_MS);
            if(!topLedFlag)
                led_top_off();
            led_2_off();

            vTaskDelay((LED_BLINK_DELAY * 2) / portTICK_PERIOD_MS);

            topLedFlag = !topLedFlag;
        }
    }

    public:
    bool isBlinking()
    {
        if(blinkLEDsTask == NULL)
            return false;
        
        auto taskState = eTaskGetState(blinkLEDsTask);

        return taskState != eDeleted && taskState != eReady && taskState != eSuspended;
    }

    static void led_top_on()
    {
        digitalWrite(constants::pins::led::Top, HIGH);
        digitalWrite(5, HIGH);
    }
    static void led_1_on()
    {
        digitalWrite(constants::pins::led::Led1, HIGH);
    }
    static void led_2_on()
    {
        digitalWrite(constants::pins::led::Led2, HIGH);
    }
    static void led_top_off()
    {
        digitalWrite(constants::pins::led::Top, LOW);
        digitalWrite(5, LOW);
    }
    static void led_1_off()
    {
        digitalWrite(constants::pins::led::Led1, LOW);
    }
    static void led_2_off()
    {
        digitalWrite(constants::pins::led::Led2, LOW);
    }
    
    Led()
    {
        pinMode(constants::pins::led::Top, OUTPUT);
        pinMode(constants::pins::led::Led1, OUTPUT);
        pinMode(constants::pins::led::Led2, OUTPUT);
        led_top_off();
        led_1_off();
        led_2_off();
    }

    void StartBlink()
    {
        if(isBlinking())
            return;

        xTaskCreatePinnedToCore(
            BlinkLEDsTask,
            "BlinkLEDsTask",
            1000,
            NULL,
            0,
            &blinkLEDsTask,
            0);
    }

    void StopBlink()
    {
        if(isBlinking())
        {
            vTaskDelete(blinkLEDsTask);
        }
        led_top_off();
        led_1_off();
        led_2_off();
    }

    void Toggle()
    {
        if(isBlinking())
            StopBlink();
        else
            StartBlink();
    }
};