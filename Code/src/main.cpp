#include <Arduino.h>
#include "motor/movement.h"
#include "sdIO/sdcardIO.h"

Movement movement;

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println(("Firmware version: " + std::string(constants::version)).c_str());
  sdcardIO::MountCard();
  movement.init();
  movement.SPEED = MAX_MOTOR_SPEED;
  movement.DIRECTION = 0;
  movement.Apply();
}

// the loop function runs over and over again until power down or reset
void loop() {
  movement.HandleControllerInputs();
}