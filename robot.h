#pragma once

#include "motors.h"
#include "linesensor.h"

#define RIGHT_MOTOR_PIN 5      // left motor digital pin
#define LEFT_MOTOR_PIN 4       // right motor digital pin

#define LEFT_SENSOR_PIN 0      // left IR sensor
#define RIGHT_SENSOR_PIN 1     // right IR sensor

class Robot
{
  public:
    Robot();
    Robot(LineSensor& lineSensor, Motors& motors);
    void begin();
    void loop();
    void stayOnLine(byte speedPercent);
    
  private:
    LineSensor mLineSensor;
    Motors mMotors;
};