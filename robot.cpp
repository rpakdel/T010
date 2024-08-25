#include "Arduino.h"
#include "robot.h"

Robot::Robot() :
  mLineSensor(LineSensor(LEFT_SENSOR_PIN, RIGHT_SENSOR_PIN)),
  mMotors(Motors(LEFT_MOTOR_PIN, RIGHT_MOTOR_PIN))
{

}

Robot::Robot(LineSensor& lineSensor, Motors& motors) :
  mLineSensor(lineSensor),
  mMotors(motors)
{

}

void Robot::begin()
{
  mLineSensor.begin();
  mMotors.begin();
}

void Robot::loop()
{
  mLineSensor.loop();
  mMotors.loop();
}

void Robot::stayOnLine(byte speedPercent)
{
  LineSensorStatus s = mLineSensor.getStatus();
  if (s.leftOnBlack)
  {
    mMotors.turnRight(speedPercent, 50);  
  }
  else if (s.rightOnBlack)
  {
    mMotors.turnLeft(speedPercent, 50);
  }
  else
  {
    mMotors.moveForward(speedPercent, 50);
  }
}