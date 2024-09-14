#pragma once

#include "motors.h"
#include "linesensor.h"
#include "config.h"

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