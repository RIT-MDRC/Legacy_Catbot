#include <Arduino.h>
#include "Potentiometer.h"

// Represents a potentiometer that is attached to a hip of the robot.
// _pin: The analog pin the potentiometer is connected to (e.g. A0)
// _maxDeg: The maximum rotation of the potentiometer, in degrees
// _maxValue: The maximum raw value that the potentiometer can output (default is 1023)
Potentiometer::Potentiometer(int _pin, int _maxDeg, int _maxValue = 1023)
{
  pin = _pin;
  maxDeg = _maxDeg;
  maxValue = _maxValue;

  pinMode(pin, INPUT);
};

// Converts raw data to a rotational degree value.
// Starts at zero, and increases as potentiometer is rotated counterclockwise.
float Potentiometer::getReading()
{
  float potVar = analogRead(pin);
  return potVar / maxValue * maxDeg;
}

// Gets current degree reading as an integer value.
int Potentiometer::getReadingInt() { return (int)ceil(getReading()); }
