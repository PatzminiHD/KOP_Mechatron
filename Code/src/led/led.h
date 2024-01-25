#include <Arduino.h>
#include "../vars/constants.h"

#define LED_BLINK_DELAY 100

class Led
{
    private:
    TaskHandle_t blinkLEDsTask;

    static void led_top_on()
    {
        ledcWrite(constants::pins::led::Top_Channel, 255);
    }
    static void led_1_on()
    {
        ledcWrite(constants::pins::led::Led1_Channel, 255);
    }
    static void led_2_on()
    {
        ledcWrite(constants::pins::led::Led2_Channel, 255);
    }
    static void led_top_off()
    {
        ledcWrite(constants::pins::led::Top_Channel, 0);
    }
    static void led_1_off()
    {
        ledcWrite(constants::pins::led::Led1_Channel, 0);
    }
    static void led_2_off()
    {
        ledcWrite(constants::pins::led::Led2_Channel, 0);
    }

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
    bool isBlinking;
    
    Led()
    {
        ledcSetup(constants::pins::led::Top_Channel, 500, 8);
        ledcSetup(constants::pins::led::Led1_Channel, 500, 8);
        ledcSetup(constants::pins::led::Led2_Channel, 500, 8);
        ledcAttachPin(constants::pins::led::Top, constants::pins::led::Top_Channel);
        ledcAttachPin(constants::pins::led::Led1, constants::pins::led::Led1_Channel);
        ledcAttachPin(constants::pins::led::Led2, constants::pins::led::Led2_Channel);
    }

    void StartBlink()
    {
        if(isBlinking)
            return;

        xTaskCreatePinnedToCore(
            BlinkLEDsTask,
            "BlinkLEDsTask",
            1000,
            NULL,
            0,
            &blinkLEDsTask,
            0);

        isBlinking = false;
    }

    void StopBlink()
    {
        vTaskSuspend(blinkLEDsTask);
        vTaskDelete(blinkLEDsTask);
        
        led_top_off();
        led_1_off();
        led_2_off();
        isBlinking = false;
    }
};