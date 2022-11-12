#ifndef Potentiometer_h
#define Potentiometer_h

#include <Arduino.h>

// Represents a potentiometer that is attached to a hip of the robot.
class Potentiometer
{
public:
  Potentiometer(int _pin, int _maxDeg, int _maxValue = 1023)
  {
    pin = _pin;
    maxDeg = _maxDeg;
    maxValue = _maxValue;

    pinMode(pin, INPUT);
  };

  // Converts raw data to a rotational degree value.
  // Starts at zero, and increases as potentiometer is rotated counterclockwise.
  float getReading()
  {
    float potVar = analogRead(pin);
    return potVar / maxValue * maxDeg;
  }

  // Gets current degree reading as an integer value.
  int getReadingInt() { return (int)ceil(getReading()); }

private:
  int pin;          // Pin that will read potentiometer values
  int maxDeg;       // Maximum rotation of the potentiometer (degrees)
  int maxValue;     // Maximum raw output value of the potentiometer (usually is 1023)
};

#endif
