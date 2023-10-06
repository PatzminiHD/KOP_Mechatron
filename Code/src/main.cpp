#include <Arduino.h>
#include "motor/movement.h"
//#include "controller/controller.h"

Movement movement;
//XboxController controller;

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println(("Firmware version: " + std::string(constants::version)).c_str());
  movement.init();
  //controller.init();
  movement.SPEED = MAX_MOTOR_SPEED;
  movement.DIRECTION = 0;
  movement.Apply();
}

// the loop function runs over and over again until power down or reset
void loop() {
  for(int i = 0; i < 360; i++)
  {
    movement.DIRECTION = i;
    movement.Apply();
    delay(5);
  }
}
