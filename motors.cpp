#include "motors.h"
#include "config.h"

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
  // NOOP
  #ifndef TEST_MODE
    // NOOP
  #else
    testLoop();
  #endif 
}

void Motors::testLoop()
{
  Serial.println(F("LEFT MOTOR SPINNING 3000 MS"));
  rotateLeftMotor(10);
  delay(3000);
  rotateLeftMotor(0);
  delay(1000);
  
  Serial.println(F("RIGHT MOTOR SPINNING 3000 MS"));
  rotateRightMotor(10);
  delay(3000);
  rotateRightMotor(0);
  delay(1000);
}

void Motors::stopMove()
{
  rotateLeftMotor(0);
  rotateRightMotor(0);
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
  moveStraight(speedPercent);
  delay(delayMS);
}

void Motors::moveReverse(byte speedPercent, int delayMS)
{
  moveStraight(-1 * speedPercent);
  delay(delayMS);
}

void Motors::moveStraight(byte speedPercent)
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
  return speedPercent;
  if (speedPercent <= MOTOR_MIN_PERCENT && speedPercent > 0)
  {
    speedPercent = MOTOR_MIN_PERCENT;
  }

  if (speedPercent >= -MOTOR_MIN_PERCENT && speedPercent < 0)
  {
    speedPercent = -MOTOR_MIN_PERCENT;
  }

  return speedPercent;
}