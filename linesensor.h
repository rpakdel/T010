#pragma once

#include <Arduino.h>
#include "linesensorvalues.h"
#include "linesensorstatus.h"

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
    void recaliberate();
    void printValues(Print& printer, char* prefix, LineSensorValues svalues);
    void printStatus(Print& printer, LineSensorStatus status);
    void readAndRecaliberate();
    void testLoop();
};