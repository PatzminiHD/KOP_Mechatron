#include <Arduino.h>
#include "motor/movement.h"

Movement movement;

void setup() {
  Serial.begin(115200);
  delay(100);
  Serial.println(("Firmware version: " + std::string(constants::version)).c_str());
}

// the loop function runs over and over again until power down or reset
void loop() {
}
