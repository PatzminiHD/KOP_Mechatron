#include <Arduino.h>
#define STEPPER_FULL_STEPS_IN_FULL_ROTATION       200


#define STEPPER_MAX_SPEED        2     //Maximum Speed in Rotations per second
#define STEPPER_MAX_ACCELERATION 5     //Maximum Acceleration in Full Steps per second per second

#define STEPPER_MAX_FULL_STEPS_PER_SECOND STEPPER_FULL_STEPS_IN_FULL_ROTATION*STEPPER_MAX_SPEED

class Stepper
{
    private:
        uint8_t _stepPin, _dirPin, _m0Pin, _m1Pin, _m2Pin;
        uint16_t _currSpeed = 0;
        bool _currDirection = false;

        void UpdateSpeedAndDirection()
        {
            digitalWrite(_dirPin, _currDirection);
            if(_currSpeed == 0)
            {
                OCR1A = 65535;  //Disable Steps
            }
            uint32_t divisor = 1024;
            divisor *= _currSpeed;

            if(OCR1A == 16000000/(divisor) - 1)
            {
                return;
            }
            TCNT1  = 0;
            OCR1A = 16000000/(divisor) - 1;
        }

    public:
        uint8_t _movementMode;
        uint16_t targetSpeed;
        bool targetDirection;
        enum MovementMode
        {
            MOVEMENT_MODE_FULL = 1,
            MOVEMENT_MODE_HALF = 2,
            MOVEMENT_MODE_QUARTER = 4,
            MOVEMENT_MODE_EIGTH = 8,
            MOVEMENT_MODE_SIXTEENTH = 16,
        };

        Stepper(uint8_t stepPin, uint8_t dirPin, uint8_t m0Pin, uint8_t m1Pin, uint8_t m2Pin, MovementMode moveMode)
        {
            _stepPin = stepPin;
            _dirPin = dirPin;
            _m0Pin = m0Pin;
            _m1Pin = m1Pin;
            _m2Pin = m2Pin;
            _movementMode = moveMode;
            targetSpeed = 0;
            targetDirection = false;
            UpdateMovementMode();
        }

        void ReachSpeedTarget()
        {

            if(targetSpeed > STEPPER_MAX_FULL_STEPS_PER_SECOND * _movementMode)
            {
                targetSpeed = STEPPER_MAX_FULL_STEPS_PER_SECOND * _movementMode;
            }
            if(targetDirection != _currDirection) //Decelerate to 0, then switch direction
            {
                Serial.println("\nDecelerate for direction change\nCurr Dir: " + (String)_currDirection);
                for (uint16_t i = _currSpeed; i > 0; i--)
                {
                    _currSpeed = i;
                    UpdateSpeedAndDirection();
                    delay(1000/STEPPER_MAX_ACCELERATION);
                }
                _currDirection = !_currDirection;
                Serial.println("\nDecelerate for direction change finished");
            }

            if(targetSpeed > _currSpeed)    //Accelerate to target speed
            {
                Serial.println("\nAccelerate\nCurr Dir: " + (String)_currDirection);
                for (uint16_t i = _currSpeed; i < targetSpeed + 1; i++)
                {
                    _currSpeed = i;
                    UpdateSpeedAndDirection();
                    delay(1000/STEPPER_MAX_ACCELERATION);
                }
                Serial.println("\nAccelerate finished\nTarget: " + (String)targetSpeed + "Curr: " + (String)_currSpeed);
            }
            else //Decelerate to targe speed
            {
                Serial.println("\nDecelerate\nCurr Dir: " + (String)_currDirection);
                for (uint16_t i = _currSpeed; i > targetSpeed; i--)
                {
                    _currSpeed = i;
                    UpdateSpeedAndDirection();
                    delay(1000/STEPPER_MAX_ACCELERATION);
                }
                _currSpeed = targetSpeed;
                UpdateSpeedAndDirection();
                Serial.println("\nDecelerate finished\nTarget: " + (String)targetSpeed + "Curr: " + (String)_currSpeed);
            }
        }

        void SetSpeed(uint16_t degreesPerSecond)
        {
            Serial.print("Set Speed: ");
            Serial.println(degreesPerSecond);
            targetSpeed = (degreesPerSecond / 360.0) * STEPPER_FULL_STEPS_IN_FULL_ROTATION * _movementMode;
            Serial.println(targetSpeed);
        }

        void MakeStep()
        {
            digitalWrite(_stepPin, HIGH);
            delayMicroseconds(1);
            digitalWrite(_stepPin, LOW);
        }
        
        void UpdateMovementMode()
        {
            uint16_t targetSpeedPrev = targetSpeed;
            targetSpeed = 0;
            ReachSpeedTarget();
            switch(_movementMode)
            {
                case MOVEMENT_MODE_FULL:
                    digitalWrite(_m0Pin, LOW);
                    digitalWrite(_m1Pin, LOW);
                    digitalWrite(_m2Pin, LOW);
                    break;
                case MOVEMENT_MODE_HALF:
                    digitalWrite(_m0Pin, HIGH);
                    digitalWrite(_m1Pin, LOW);
                    digitalWrite(_m2Pin, LOW);
                    break;
                case MOVEMENT_MODE_QUARTER:
                    digitalWrite(_m0Pin, LOW);
                    digitalWrite(_m1Pin, HIGH);
                    digitalWrite(_m2Pin, LOW);
                    break;
                case MOVEMENT_MODE_EIGTH:
                    digitalWrite(_m0Pin, HIGH);
                    digitalWrite(_m1Pin, HIGH);
                    digitalWrite(_m2Pin, LOW);
                    break;
                case MOVEMENT_MODE_SIXTEENTH:
                    digitalWrite(_m0Pin, HIGH);
                    digitalWrite(_m1Pin, HIGH);
                    digitalWrite(_m2Pin, HIGH);
                    break;

                default:    //Set to full step
                    digitalWrite(_m0Pin, LOW);
                    digitalWrite(_m1Pin, LOW);
                    digitalWrite(_m2Pin, LOW);
                    break;
            }
            targetSpeed = targetSpeedPrev;
            ReachSpeedTarget();
        }
};