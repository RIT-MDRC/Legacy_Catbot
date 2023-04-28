#include <Arduino.h>
#include "Potentiometer.h"

// Represents a potentiometer that is attached to a hip of the robot.
// _pin: The analog pin the potentiometer is connected to (e.g. A0)
// _maxDeg: The maximum rotation of the potentiometer, in degrees
// _maxValue: The maximum raw value that the potentiometer can output (default is 1023)
Potentiometer::Potentiometer(int _pin, int _maxDeg, int _maxValue = 800)
{
  pin = _pin;
  maxDeg = _maxDeg;
  maxValue = _maxValue;

  pinMode(pin, INPUT);
  getRawReading();
};

// Converts raw data to a rotational degree value.
// Starts at zero, and increases as potentiometer is rotated counterclockwise.
int Potentiometer::getReading()
{
  int potVar = getRawReading();
  return potVar / maxValue * maxDeg;
}

// Gets current degree reading as an integer value.
int Potentiometer::getReadingInt() { return (int)ceil(getReading()); }

int Potentiometer::getRawReading()
{
  lastRawReading = analogRead(pin);
  return lastRawReading;
}

/**
 * check if the potentiometer is in a range (inclusive on both ends)
 */
bool Potentiometer::isInRawValue(int minRawVal, int maxRawVal)
{
  int value = getRawReading();
  return value >= minRawVal && value <= maxRawVal;
}

/**
 * check if the potentiometer is in a range (inclusive on both ends)
 */
bool Potentiometer::isInDegree(int minDeg, int maxDeg)
{
  int value = getReading();
  return value >= minDeg && value <= maxDeg;
}

/**
 *
 */
bool Potentiometer::isMoving(int tolerance = 1)
{
  int dif = fabs(lastRawReading - getRawReading());
  return dif > tolerance;
}

bool Potentiometer::isCloseToEdge(int tolerance = 50)
{
  int value = getRawReading();
  return value <= tolerance || value >= maxValue - tolerance;
}

bool Potentiometer::isBottomHalf()
{
  return getRawReading() < maxValue / 2;
}