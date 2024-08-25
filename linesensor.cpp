#include "linesensor.h"

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
  mBase = readSensors(SENSOR_READ_WINDOW);
}

void LineSensor::loop()
{
  LineSensorValues current = readSensors(SENSOR_READ_WINDOW);
  printValues(Serial, "BASE-", mBase);
  printValues(Serial, "CURRENT-", current);
  mStatus = compareSensorValues(mBase, current);
  printStatus(Serial, mStatus);
  caliberate();
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
  if (current.left > (base.left + SENSOR_MARGIN)) 
  {
    status.leftOnBlack = 1;
  }

  if (current.right > (base.right + SENSOR_MARGIN)) 
  {
    status.rightOnBlack = 1;
  }
  return status;
}

void LineSensor::caliberate()
{
  mReadCount++;
  if (mReadCount >= RECALIBERATION)
  {
    Serial.println(F("-----RECALIBERATION-----"));
    mBase = readSensors(SENSOR_READ_WINDOW);
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
