#ifndef Potentiometer_h
#define Potentiometer_h

#include "Arduino.h"

// Represents a potentiometer that is attached to a hip of the robot.
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

  // An event that is triggered whenever the potentiometer is rotated. The value passed is
  // the new current potentiometer rotation (in degrees). Any method that is subscribed to this
  // event should have a single int parameter.
  __event void RotationChangeEvent(int current);

  // Triggers the RotationChangeEvent when a rotation difference is detected.
  void listenForRotation()
  {
    if (getReading() != prevRotation)
    {
      prevRotation = getReading();
      __raise RotationChangeEvent(prevRotation);
    }
  }

private:
  int pin;          // Pin that will read potentiometer values
  int maxDeg;       // Maximum rotation of the potentiometer (degrees)
  int maxValue;     // Maximum raw output value of the potentiometer
  int prevRotation; // The rotation the potentiometer was at during the last Arduino loop
};

#endif
