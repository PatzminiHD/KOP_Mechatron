#include "rotary_encoder.h"

uint8_t RotaryEncoder::clockPin;
uint8_t RotaryEncoder::dtPin;
uint8_t RotaryEncoder::buttonPin;

volatile int8_t RotaryEncoder::moves;
volatile int8_t RotaryEncoder::movesToMake;
volatile bool RotaryEncoder::buttonPressed;