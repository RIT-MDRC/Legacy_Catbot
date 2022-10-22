#ifndef Potentiometer_h
#define Potentiometer_h

#include "Arduino.h"

class Potentiometer
{
public:
  Potentiometer(int _pin, int _maxDeg, int _maxValue)
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

private:
  int pin;        // Pin that will read potentiometer values
  int maxDeg;     // Maximum rotation of the potentiometer (degrees)
  int maxValue;   // Maximum raw output value of the potentiometer
};



#endif
