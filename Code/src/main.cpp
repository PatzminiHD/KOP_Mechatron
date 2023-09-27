#include <Arduino.h>
#include "motor/movement.h"

Movement movement;

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println(("Firmware version: " + std::string(constants::version)).c_str());
  movement.init();
  movement.SPEED = 500;
  movement.DIRECTION = 0;
  movement.Apply();
}

// the loop function runs over and over again until power down or reset
void loop() {
}
