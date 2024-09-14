#include "linesensor.h"
#include "config.h"

LineSensor::LineSensor(byte leftSensorAnalogPin, byte rightSensorAnalogPin) :
  mLeftAPin(leftSensorAnalogPin), 
  mRightAPin(rightSensorAnalogPin)
{

}

LineSensor::LineSensor(const LineSensor& copyFrom) :
  mLeftAPin(copyFrom.mLeftAPin),
  mRightAPin(copyFrom.mRightAPin)
{

}

void LineSensor::begin()
{
  pinMode(mLeftAPin, INPUT);
  pinMode(mRightAPin, INPUT);
  caliberate();
}

void LineSensor::loop()
{
  #ifndef TEST_MODE
    readAndRecaliberate();
  #else
    testLoop();
  #endif
}

void LineSensor::readAndRecaliberate()
{
  LineSensorValues current = readSensors(IRSENSOR_READ_WINDOW);
  //printValues(Serial, "BASE-", mBase);
  //printValues(Serial, "CURRENT-", current);
  mStatus = compareSensorValues(mBase, current);
  printStatus(Serial, mStatus);
  recaliberate();
}

void LineSensor::testLoop()
{
  LineSensorValues current = readSensors(IRSENSOR_READ_WINDOW);
  printValues(Serial, "TEST-", current);
}

LineSensorStatus LineSensor::getStatus()
{
  return mStatus;
}

LineSensorValues LineSensor::readSensors(byte readCount)
{
  int accumulator[] = {0, 0};
  for(int i = 0; i < readCount; i++)
  {
    accumulator[0] += analogRead(mLeftAPin);
    accumulator[1] += analogRead(mRightAPin);
    delay(1);
  }

  LineSensorValues values;
  values.left = accumulator[0] / readCount;
  values.right = accumulator[1] / readCount;
  return values;
}

LineSensorStatus LineSensor::compareSensorValues(LineSensorValues base, LineSensorValues current)
{
  LineSensorStatus status = { 0, 0 };
  if (current.left > (base.left + IRSENSOR_DELTA_THRESH)) 
  {
    status.leftOnBlack = 1;
  }

  if (current.right > (base.right + IRSENSOR_DELTA_THRESH)) 
  {
    status.rightOnBlack = 1;
  }
  return status;
}

void LineSensor::caliberate()
{
    Serial.println(F("-----CALIBERATION-----"));
    mBase = readSensors(IRSENSOR_READ_WINDOW);
    mReadCount = 0;
}

void LineSensor::recaliberate()
{
  mReadCount++;
  if (mReadCount >= IRSENSOR_RECALIBERATION)
  {
    Serial.println(F("-----RECALIBERATION-----"));
    mBase = readSensors(IRSENSOR_READ_WINDOW);
    mReadCount = 0;
  }
}

void LineSensor::printValues(Print& printer, char* prefix, LineSensorValues svalues)
{
  printer.print(prefix);
  printer.print(F("LEFT:"));
  printer.print(svalues.left);
  printer.print(F(","));
  printer.print(prefix);
  printer.print(F("RIGHT:"));
  printer.println(svalues.right);
}

void LineSensor::printStatus(Print& printer, LineSensorStatus status)
{
  printer.print(F("LEFT-BLACK:"));
  printer.print(status.leftOnBlack);
  printer.print(",");
  printer.print(F("RIGHT-BLACK:"));
  printer.print(status.rightOnBlack);
  printer.println();
}
