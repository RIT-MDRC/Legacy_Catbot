#ifndef Potentiometer_h
#define Potentiometer_h

//Motor class for CatBot hip joints
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

  float getReading()
  {
    float potVar = analogRead(pin);
    return potVar / maxValue * maxDeg;
  }

private:
  int pin;
  int maxDeg;
  int maxValue;
};



#endif
