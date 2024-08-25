#include <Arduino.h>
#include "robot.h"

//LineSensor lineSensor(LEFT_SENSOR_PIN, RIGHT_SENSOR_PIN);
//Motors motors(LEFT_MOTOR_PIN, RIGHT_MOTOR_PIN);
//Robot robot(lineSensor, motors);

Robot robot;

void setup() 
{
  Serial.begin(115200);
  robot.begin();
}

void move()
{
  int speed=6;
  
}

void loop() 
{
  robot.loop();
  robot.stayOnLine(6);
}
