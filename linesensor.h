#pragma once

#include <Arduino.h>
#include "linesensorvalues.h"
#include "linesensorstatus.h"

#define SENSOR_MARGIN 5        // how much change from base to detect black line
#define SENSOR_READ_WINDOW 20  // how many values to average
#define RECALIBERATION 200     // recaliberate after this many reads

class LineSensor
{
  public:
    
    LineSensor(byte leftSensorAnalogPin, byte rightSensorAnalogPin);
    LineSensor(const LineSensor& copyFrom);
    void begin();
    void loop();
    LineSensorStatus getStatus();

  private:
    byte mLeftAPin;
    byte mRightAPin;
    LineSensorValues mBase;
    LineSensorStatus mStatus;
    int mReadCount;

    LineSensorStatus compareSensorValues(LineSensorValues base, LineSensorValues current);
    LineSensorValues readSensors(byte readCount);
    void caliberate();
    void printValues(Print& printer, char* prefix, LineSensorValues svalues);
    void printStatus(Print& printer, LineSensorStatus status);
};