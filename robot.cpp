#include "Arduino.h"
#include "robot.h"

Robot::Robot() :
  mLineSensor(LineSensor(IRSENSOR_LEFT_PIN, IRSENSOR_RIGHT_PIN)),
  mMotors(Motors(MOTOR_LEFT_PIN, MOTOR_RIGHT_PIN))
{

}

Robot::Robot(LineSensor& lineSensor, Motors& motors) :
  mLineSensor(lineSensor),
  mMotors(motors)
{

}

void Robot::begin()
{
  // wait until robot is put on the ground
  delay(ROBOT_INIT_DELAY);
  mLineSensor.begin();
  mMotors.begin();
}

void Robot::loop()
{
  mLineSensor.loop();
  mMotors.loop();
  #ifndef TEST_MODE
    stayOnLine(ROBOT_SPEED);
  #endif
}

void Robot::stayOnLine(byte speedPercent)
{
  LineSensorStatus s = mLineSensor.getStatus();
  if (s.leftOnBlack && !s.rightOnBlack)
  {
    mMotors.turnLeft(speedPercent / 2, ROBOT_MOVE_DELAY);  
  }
  else if (s.rightOnBlack && !s.leftOnBlack)
  {
    mMotors.turnRight(speedPercent / 2, ROBOT_MOVE_DELAY);
  }
  else if (!s.rightOnBlack && !s.leftOnBlack)
  {
    mMotors.moveForward(speedPercent, ROBOT_MOVE_DELAY);
  }
  else
  {
    // if both are on black, just keep moving forward slowly for now
    mMotors.moveForward(speedPercent / 2, ROBOT_MOVE_DELAY);
  }
}