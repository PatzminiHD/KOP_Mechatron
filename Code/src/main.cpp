#include <Arduino.h>
#include <SPIFFS.h>
#include "motor/movement.h"
#include "sdIO/sdcardIO.h"
#include "music/MP3.h"

Movement movement;

std::string MP3::mp3File;
int MP3::VOLUME;

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println(("Firmware version: " + std::string(constants::version)).c_str());
  sdcardIO::MountCard();
  movement.init();
  
}

// the loop function runs over and over again until power down or reset
void loop() {
  movement.HandleControllerInputs();
}