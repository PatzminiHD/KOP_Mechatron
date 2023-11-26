#include <Arduino.h>
#include "stepper.h"
#include "display.h"

Stepper stepper(0, 0, 0, 0, 0, Stepper::MOVEMENT_MODE_FULL);
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

  display.init();

  display.line0 = "Line0";
  display.line1 = "Line1, but its longer then the line";
  display.line2 = "Line2";
  display.line3 = "Last line";

  stepper.targetSpeed = 200;
  stepper.ReachSpeedTarget();
  stepper.targetDirection = !stepper.targetDirection;
  stepper.ReachSpeedTarget();
  stepper.targetSpeed = 0;
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
