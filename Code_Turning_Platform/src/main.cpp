#include <Arduino.h>
#include "stepper.h"
#include "display.h"
#include <LiquidCrystal_I2C.h>

const uint8_t stepperPins[5] = {
  7, 6, 10, 9, 8
};


Stepper stepper(stepperPins[0], stepperPins[1], stepperPins[2], stepperPins[3], stepperPins[4], Stepper::MOVEMENT_MODE_SIXTEENTH);
Display display;


size_t numOfPersons = 0;
void MainMenu();
void DoNothing() { ; }
void UpdateNumOfPersons()
{
  display.UpdateInt(&numOfPersons, 1, "Num. of Pers.");
  Serial.print("Updated NumOfPersons: ");
  Serial.println(numOfPersons);
  MainMenu();
}
void SubMenu1()
{
  display.cursorPos = 0;
  display.Clear();
  display.menuEntries.push_back({"Go back", MainMenu});
  display.menuEntries.push_back({"DoNothingLine", DoNothing});
  display.Update();
}
void SubMenu2()
{
  display.cursorPos = 0;
  display.Clear();
  display.menuEntries.push_back({"Go back", MainMenu});
  display.menuEntries.push_back({"Number of Persons", UpdateNumOfPersons});
  display.menuEntries.push_back({"DoNothingLine0", DoNothing});
  display.menuEntries.push_back({"DoNothingLine1", DoNothing});
  display.menuEntries.push_back({"DoNothingLine2", DoNothing});
  display.menuEntries.push_back({"DoNothingLine3", DoNothing});
  display.menuEntries.push_back({"DoNothingLine4", DoNothing});
  display.Update();
}
void MainMenu()
{
  display.cursorPos = 0;
  display.Clear();
  display.menuEntries.push_back({"TurnTable", DoNothing});
  display.menuEntries.push_back({"Number of Persons", UpdateNumOfPersons});
  display.menuEntries.push_back({"EmptyLine", DoNothing});
  display.menuEntries.push_back({"SubMenu1", SubMenu1});
  display.menuEntries.push_back({"SubMenu2", SubMenu2});
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
