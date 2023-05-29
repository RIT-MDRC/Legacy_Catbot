#include "MotorController.h"
#include <Arduino.h>

#define DEFAULT_SPEED (20)
#define SETPOINT_TOLERANCE_DEGREES 4

MotorController::MotorController(Motor *_motor, Potentiometer *_pot)
{
  motor = _motor;
  pot = _pot;
}

/**
 * Uses the current potentiometer value as the 0 setpoint spot
 */
void MotorController::calibrate()
{
}

// Stop Motor
void MotorController::stop()
{
  motor->arm();
}

// Turn motor by the amount of degrees with a given speed
void MotorController::turn(int setpoint, int speedPercent)
{
  int initialDeg = pot->getReading();
  int finalSpeed = setpoint < 0 ? -speedPercent : speedPercent;
  while (pot->inDegRange() && pot->getReading() < initialDeg + setpoint)
  {
    motor->runCall(finalSpeed);
  }
  stop();
}

// Turn motor by the amount of degrees with default speed
void MotorController::turn(int setpoint)
{
  turn(setpoint, DEFAULT_SPEED);
}

// Turn the motor to a specific setpoint with a given speed
void MotorController::turnTo(int setpoint, int speedPercent)
{
  // make sure setpoint is in the valid range
  if (pot->getMinDegrees() > setpoint || pot->getMaxDegrees() < setpoint)
    return;

  // figure out which direction to turn
  int initialDeg = pot->getReading();
  int direction = setpoint > initialDeg ? 1 : -1;

  // while we are not yet at the setpoint...
  // (and make sure that the pot is in a valid range, just in case!)
  while (pot->inDegRange() && !isAtSetpoint(setpoint, direction))
  {
    // ...move the motor towards the setpoint
    motor->runCall(direction * speedPercent);
  }

  // motion is done - turn off the motor
  stop();
}

// Turn the motor to a specific setpoint with a default speed
void MotorController::turnTo(int setpoint)
{
  turnTo(setpoint, DEFAULT_SPEED);
}

// Turn the motor to a specific setpoint within a given time
// TODO: Implement next semester
void MotorController::turnToWithin(int setpoint, int time)
{
}

int MotorController::getCurrentDegree()
{
  return pot->getReading();
}

int MotorController::getMinDegrees()
{
  return pot->getMinDegrees();
}

int MotorController::getMaxDegrees()
{
  return pot->getMaxDegrees();
}

int MotorController::getDistanceToMax()
{
  return getMaxDegrees() - pot->getReading();
}

int MotorController::getDistanceToMin()
{
  return pot->getReading() - getMinDegrees();
}

int MotorController::getDegreesToClosest()
{
  return min(getDistanceToMax(), getDistanceToMin());
}

int MotorController::getDirectionToClosest()
{
  return getDistanceToMax() < getDistanceToMin() ? 1 : -1;
}

int MotorController::getDirectionToFarthest()
{
  return getDistanceToMax() > getDistanceToMin() ? 1 : -1;
}

int MotorController::getDirectionToMax()
{
  return getDistanceToMax() > 0 ? 1 : 0;
}

int MotorController::getDirectionToMin()
{
  return getDistanceToMin() > 0 ? -1 : 0;
}

void MotorController::printPotLocationInLoop(int delayTime)
{
  while (true)
  {
    Serial.println(pot->getReading());
    delay(delayTime);
  }
}

bool MotorController::isAtSetpoint(double setpoint, int direction)
{
  int value = pot->getReading();
  Serial.println(String(value) + " " + String(setpoint) + " " + String(direction));
  return (setpoint - value) * direction < SETPOINT_TOLERANCE_DEGREES;
}