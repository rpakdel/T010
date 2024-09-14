#pragma once

#include <Arduino.h>
#include <Servo.h>

class Motors
{
  public:
    Motors(byte leftMotorPin, byte rightMotorPin);
    Motors(const Motors& copyFrom);
    void begin();
    void loop();
    void turnLeft(byte speedPercent, int delayMS);
    void turnRight(byte speedPercent, int delayMS);
    void moveForward(byte speedPercent, int delayMS);
    void moveReverse(byte speedPercent, int delayMS);
    void stopMove();

  private: 
    byte mLeftMotorPin;
    byte mRightMotorPin;
    Servo mRightMotor;
    Servo mLeftMotor;
    byte clampSpeedPercent(byte speedPercent);
    byte getRightDegree(byte speedPercent);
    byte getLeftDegree(byte speedPercent);
    void rotateLeftMotor(byte speedPercent);
    void rotateRightMotor(byte speedPercent);
    void moveStraight(byte speedPercent);
    void testLoop();
};