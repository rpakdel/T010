#include "motors.h"

Motors::Motors(byte leftMotorPin, byte rightMotorPin) :
  mLeftMotorPin(leftMotorPin),
  mRightMotorPin(rightMotorPin)
{

}

Motors::Motors(const Motors& copyFrom) :
  mLeftMotorPin(copyFrom.mLeftMotorPin),
  mRightMotorPin(copyFrom.mRightMotorPin)
{

}

void Motors::begin()
{
  pinMode(mRightMotorPin, OUTPUT);
  pinMode(mLeftMotorPin, OUTPUT);
  mRightMotor.attach(mRightMotorPin);
  mLeftMotor.attach(mLeftMotorPin);
}

void Motors::loop()
{

}

void Motors::turnLeft(byte speedPercent, int delayMS)
{
  rotateLeftMotor(0);
  rotateRightMotor(speedPercent);
  delay(delayMS);
}

void Motors::turnRight(byte speedPercent, int delayMS)
{
  rotateRightMotor(0);
  rotateLeftMotor(speedPercent);
  delay(delayMS);
}

void Motors::moveForward(byte speedPercent, int delayMS)
{
  move(speedPercent);
  delay(delayMS);
}

void Motors::moveReverse(byte speedPercent, int delayMS)
{
  move(-1 * speedPercent);
  delay(delayMS);
}

void Motors::move(byte speedPercent)
{
  rotateLeftMotor(speedPercent);
  rotateRightMotor(speedPercent);
}

void Motors::rotateLeftMotor(byte speedPercent)
{
  mLeftMotor.write(getLeftDegree(speedPercent));
}

void Motors::rotateRightMotor(byte speedPercent)
{
  mRightMotor.write(getRightDegree(speedPercent));
}

byte Motors::getRightDegree(byte speedPercent)
{
  speedPercent = clampSpeedPercent(speedPercent);
  return 90 - (90 * speedPercent / 100);
}

byte Motors::getLeftDegree(byte speedPercent)
{
  speedPercent = clampSpeedPercent(speedPercent);
  return 90 + (90 * speedPercent / 100);
}


byte Motors::clampSpeedPercent(byte speedPercent)
{
  if (speedPercent <= MIN_MOTOR_PERCENT && speedPercent > 0)
  {
    speedPercent = MIN_MOTOR_PERCENT;
  }

  if (speedPercent >= -MIN_MOTOR_PERCENT && speedPercent < 0)
  {
    speedPercent = -MIN_MOTOR_PERCENT;
  }

  return speedPercent;
}