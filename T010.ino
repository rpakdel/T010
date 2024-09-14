#include <Arduino.h>

#define TEST_MODE
#include "robot.h"

Robot robot;

void setup() 
{
  Serial.begin(115200);
  robot.begin();
}

void loop() 
{
  robot.loop();
}
