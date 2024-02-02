#include <Arduino.h>
#include "stepper.h"
#include "display.h"
#include <LiquidCrystal_I2C.h>

const uint8_t stepperPins[5] = {
  12, 13, 9, 10, 11
};


Stepper stepper(stepperPins[0], stepperPins[1], stepperPins[2], stepperPins[3], stepperPins[4], Stepper::MOVEMENT_MODE_SIXTEENTH);
Display display;
int64_t speed = 0;

int64_t numOfPersons = 0;

void MainMenu(uint8_t _cursorPos = 0);
void DoNothing() { ; }

void Stop()
{
  stepper.SetSpeed(0);
  display.Clear();
  display.menuEntries.push_back({"Stopping...", DoNothing});
  display.Update();
  stepper.ReachSpeedTarget();
  rotaryEncoder.buttonPressed = false;
  rotaryEncoder.movesToMake = 0;
  MainMenu();
}
void ReachSetSpeed()
{
  stepper.SetSpeed(speed);
  display.Clear();
  display.menuEntries.push_back({"Accelerating...", DoNothing});
  display.Update();
  stepper.ReachSpeedTarget();
  rotaryEncoder.buttonPressed = false;
  rotaryEncoder.movesToMake = 0;
  MainMenu();
}
void UpdateSpeed()
{
  display.UpdateInt(&speed, 1, "Speed", -360, 360);
  MainMenu();
}
void SetSpeedZero()
{
  speed = 0;
}
void UpdateNumOfPersons()
{
  display.UpdateInt(&numOfPersons, 1, "Num. of Pers.", 0, 12);
  MainMenu(2);
}
void MainMenu(uint8_t _cursorPos = 0)
{
  display.cursorPos = _cursorPos;
  display.Clear();
  display.menuEntries.push_back({"Stop", Stop});
  display.menuEntries.push_back({"Reach Set Speed", ReachSetSpeed});
  display.menuEntries.push_back({"Set Speed", UpdateSpeed});
  display.menuEntries.push_back({"Set Speed to Zero", SetSpeedZero});
  display.Update();
}


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
  

  display.init();
  MainMenu();
  display.Update();
  //stepper.targetSpeed = 25 * stepper._movementMode;
  //stepper.ReachSpeedTarget();
}

void loop() {
  display.loop();
}

//Called when Timer1 interrupt happens
ISR(TIMER1_COMPA_vect)
{
  if(OCR1A > 15624) //If frequency is less then 1 hz, do nothing
    return;
  stepper.MakeStep();
}
