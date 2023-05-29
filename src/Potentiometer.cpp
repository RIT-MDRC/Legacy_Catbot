#include <Arduino.h>
#include "Potentiometer.h"

// Represents a potentiometer that is attached to a hip of the robot.
// _pin: The analog pin the potentiometer is connected to (e.g. A0)
// _maxDeg: The maximum rotation of the potentiometer, in degrees
// _maxValue: The maximum raw value that the potentiometer can output (default is 1023)
Potentiometer::Potentiometer(int _pin, int _maxDeg, int _minDeg = 0, int _minValue = 40, int _maxValue = 800)
{
  pin = _pin;
  maxDeg = _maxDeg;
  minDeg = _minDeg;
  maxValue = _maxValue;
  minValue = _minValue;

  centerDeg = (maxDeg + minDeg) / 2;
  centerValue = (maxValue + minValue) / 2;

  pinMode(pin, INPUT);
  getRawReading();
};

// Converts raw data to a rotational degree value.
// Starts at zero, and increases as potentiometer is rotated counterclockwise.
int Potentiometer::getReading()
{
  int potVar = getRawReading();
  return (double)potVar / (double)maxValue * (double)maxDeg;
}

// Gets current degree reading as an integer value.
int Potentiometer::getReadingInt() { return (int)ceil(getReading()); }

int Potentiometer::getRawReading()
{
  return analogRead(pin);
}

bool Potentiometer::inRawRange()
{
  return inRange(minValue, maxValue);
}

bool Potentiometer::inRawRange(int value)
{
  return inRange(minValue, maxValue, value);
}

bool Potentiometer::inDegRange()
{
  return inRange(minDeg, maxDeg);
}

bool Potentiometer::inDegRange(int value)
{
  return inRange(minDeg, maxDeg, value);
}

bool Potentiometer::inRange(int min, int max)
{
  int val = getReading();
  return inRange(min, max, val);
}

bool Potentiometer::inRange(int min, int max, int value)
{
  return min <= value && value <= max;
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

int Potentiometer::getMinDegrees()
{
  return minDeg;
}

int Potentiometer::getMaxDegrees()
{
  return maxDeg;
}

int Potentiometer::getCenterDegrees()
{
  return centerDeg;
}

bool Potentiometer::readingApproximately(int target, float threshold)
{
  return inRange(target - threshold, target + threshold);
}