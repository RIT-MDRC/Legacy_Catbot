#include "Motor.h"
#include "Potentiometer.h"
#define DELAY 100 // ms of delay between writing to ESCs

Motor::Motor(int _motorPin, int _mapLow, int _mapHigh, int _mapMiddle, bool _resetMode)
{
  motorPin = _motorPin;
  mapLow = _mapLow;
  mapHigh = _mapHigh;
  mapMiddle = _mapMiddle;
  currentDirection = 0;
  esc.attach(_motorPin);
  if (!_resetMode)
  {
    arm();
  }
}

void Motor::arm()
{
  // Stops the motor
  esc.writeMicroseconds(mapMiddle);
  currentDirection = 0;
}

void Motor::run(int speedPercent, double seconds)
{
  // Only allow speed percentages in the range [-100%, 100%]
  if (speedPercent > 100 && speedPercent < -100)
  {
    Serial.println("Speed percentage out of range. " + String(speedPercent));
    return;
  }

  // If user sets 0% speed, they're essentially just arming the motor
  if (speedPercent == 0)
  {
    arm();
    return;
  }

  // Middle value might not be in the actual center, so map() will have different
  // ranges based on where the "middle" is
  int velocity = map(speedPercent, -100, 100, mapLow, mapHigh);

  esc.writeMicroseconds(velocity);
  delay(seconds * 1000);
  arm();
}

void Motor::runCall(int speedPercent)
{

  if (speedPercent > 100 && speedPercent < -100)
  {
    return;
  }
  if (speedPercent == 0)
  {
    arm();
    return;
  }

  checkDirection(speedPercent);

  int velocity;

  velocity = map(speedPercent, -100, 100, mapLow, mapHigh);

  esc.writeMicroseconds(velocity);
  updateCurrentDirection(speedPercent);
}

void Motor::runRawValue(int value, double seconds)
{
  // check to make sure the value is in the range of the ESC
  if (value < mapLow || value > mapHigh)
  {
    Serial.println("Value out of range of ESC" + String(value) + " must be " + String(mapLow) + " to " + String(mapHigh));
    return;
  }

  int speed = map(value, mapLow, mapHigh, -100, 100);
  checkDirection(speed);

  esc.writeMicroseconds(value);
  delay(seconds * 1000);
  arm();
}

/**
 * becasue the motor can not instantly switch directions we will stop for a split second and run the opposite direction
 */
void Motor::checkDirection(int speed)
{
  if (currentDirection == 0)
  {
    return;
  }
  if ((speed > 0 && currentDirection < 0) || (speed < 0 && currentDirection > 0))
  {
    arm();
    delay(20);
  }
}

/**
 * runs the motor in reverse direction from the current speed
 * @param speed the speed to run the motor in reverse (0<=speed<=100)
 */
void Motor::runReverse(int speed)
{
  if (currentDirection == 0)
  {
    Serial.println("Motor is not running");
    return;
  }
  if (speed > 100 || speed < 0)
  {
    Serial.println("Speed percentage out of range. " + String(speed));
    return;
  }
  int direction = -currentDirection;
  int velocity = map(speed, -100, 100, mapLow, mapHigh);
  runCall(direction * velocity);
}

/**
 * move the motor away from the wall while also checking the potentiometer for the distance from the wall
 */
void Motor::moveAwayFromWall(Potentiometer *pot, int speed)
{
  if (pot->isCloseToEdge())
  {
    int direction = pot->isBottomHalf() ? 1 : -1;
    while (pot->isCloseToEdge())
    {
      runCall(direction * speed);
    }
  }
  else
  {
    Serial.println("Potentiometer is not close to the edge");
  }
  arm();
}

/**
 * update the current direction of the motor
 */
void Motor::updateCurrentDirection(int speed)
{
  currentDirection = speed / abs(speed);
}

/**
 * place the motor to the middle of the potentiometer
 */
int Motor::reset(Potentiometer *pot)
{
  if (pot->getRawReading() == 0)
  {
    Serial.println("Potentiometer is already at 0 please move it to a different position");
    return 1;
  }
  int speed = 20;
  runCall(speed);
  int lowPotValue = pot->getRawReading();
  while (pot->getRawReading() != lowPotValue)
  {
    lowPotValue = pot->getRawReading();
  }
  arm();
  if (pot->getRawReading() != 0)
  {
    Serial.println("Motor is blocked please clear space");
    return 1;
  }
  runCall(-speed);
  // get off of the limit switch
  while (pot->getRawReading() == 0)
    ;
  int highPotValue = pot->getRawReading();
  while (pot->getRawReading() != highPotValue)
  {
    highPotValue = pot->getRawReading();
  }
  arm();
  int middlePotValue = (lowPotValue + highPotValue) / 2;
  runCall(speed);
  while (!pot->isInRawValue(middlePotValue, lowPotValue))
  {
    runCall(speed);
  }
  arm();
  return 0;
}