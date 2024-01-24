#include <Arduino.h>

class uss
{
    private:


    public:
    uint8_t echoPin, triggerPin;
    uss(uint8_t _echoPin, uint8_t _triggerPin)
    {
        pinMode(_echoPin, INPUT);
        pinMode(_triggerPin, OUTPUT);
        this->echoPin = _echoPin;
        this->triggerPin = _triggerPin;
    }

    //@brief returns the distance in cm
    int MeasureDistance()
    {
        // Clears the trigPin
        digitalWrite(triggerPin, LOW);
        delayMicroseconds(2);
        // Sets the trigPin on HIGH state for 10 micro seconds
        digitalWrite(triggerPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(triggerPin, LOW);
        // Reads the echoPin, returns the sound wave travel time in microseconds
        long duration = pulseIn(echoPin, HIGH);
        // Calculating the distance
        int distance = duration * 0.034 / 2;
        return distance;
    }
};