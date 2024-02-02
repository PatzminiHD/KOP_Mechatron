#include <Arduino.h>

#define MOVES_PER_MOVE_TO_MAKE 3

class RotaryEncoder
{
    private:

    static uint8_t clockPin;
    static uint8_t dtPin;
    static uint8_t buttonPin;
    volatile static int8_t moves;

    static void InterruptMethodClock()
    {
        if(digitalRead(dtPin) != digitalRead(clockPin))
        {
            moves++;
        }
        else
        {
            moves--;
        }

        if(moves >= MOVES_PER_MOVE_TO_MAKE)
        {
            movesToMake++;
            moves = 0;
        }
        else if(moves <= -MOVES_PER_MOVE_TO_MAKE)
        {
            movesToMake--;
            moves = 0;
        }
    }

    static void InterruptMethodButton()
    {
        buttonPressed = true;
    }

    public:

    volatile static bool buttonPressed;
    volatile static int8_t movesToMake;

    void init(uint8_t _clockPin, uint8_t _dtPin, uint8_t _buttonPin)
    {
        clockPin = _clockPin;
        dtPin = _dtPin;
        buttonPin = _buttonPin;
        moves = 0;

        pinMode(clockPin, INPUT_PULLUP);
        pinMode(dtPin, INPUT_PULLUP);
        pinMode(buttonPin, INPUT_PULLUP);
        
        attachInterrupt(digitalPinToInterrupt(clockPin), InterruptMethodClock, CHANGE);
        attachInterrupt(digitalPinToInterrupt(buttonPin), InterruptMethodButton, RISING);
    }



};