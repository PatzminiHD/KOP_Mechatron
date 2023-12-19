#include <Arduino.h>
#include "stepper.h"
#include "display.h"
#include <LiquidCrystal_I2C.h>

const uint8_t stepperPins[5] = {
  11, 9, 2, 3, 4
};


Stepper stepper(stepperPins[0], stepperPins[1], stepperPins[2], stepperPins[3], stepperPins[4], Stepper::MOVEMENT_MODE_SIXTEENTH);
Display display;

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("Starting!");
  //Init Timer Interrupt
  cli(); //Stop interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A = 15625;  //Set interrupt frequenzy to just under 1hz, disabling stepper
  TCCR1B |= (1 << WGM12); //Turn on CTC Mode
  TCCR1B |= (1 << CS12) | (1 << CS10); //Set CS10 and CS12 bits for 1024 prescaler
  TIMSK1 |= (1 << OCIE1A); //Enable timer compare interrupt
  sei(); //Allow interrupts

  for (uint8_t i = 0; i < 5; i++)
  {
    pinMode(stepperPins[i], OUTPUT);
  }
  

  /*display.init();

  display.menuEntries.push_back("Hello World!");
  display.menuEntries.push_back("does this work?");
  display.menuEntries.push_back("I don't know, but I");
  display.menuEntries.push_back("don't think so");
  display.menuEntries.push_back("Line 5");
  display.menuEntries.push_back("Line 6");
  display.menuEntries.push_back("Line 7");
  display.menuEntries.push_back("Line 8");
  display.menuEntries.push_back("Line 9");
  display.menuEntries.push_back("Line 10");
  display.menuEntries.push_back("Line 11");

  display.Update();*/
  stepper.targetSpeed = 25 * stepper._movementMode;
  stepper.ReachSpeedTarget();
}

void loop() {
}

//Called when Timer1 interrupt happens
ISR(TIMER1_COMPA_vect)
{
  if(OCR1A > 15624) //If frequency is less then 1 hz, do nothing
    return;
  stepper.MakeStep();
}
