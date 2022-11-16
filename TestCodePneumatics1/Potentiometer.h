#ifndef Potentiometer_h
#define Potentiometer_h

// Potentiometer reader
// Written by: Dan and Hiro

class Potentiometer
{
public:
  Potentiometer(int _pin, int _maxDeg, int _maxValue = 1023);

  // Converts raw data to a rotational degree value.
  // Starts at zero, and increases as potentiometer is rotated counterclockwise.
  float getReading();

  // Gets current degree reading as an integer value.
  int getReadingInt();

private:
  int pin;          // Pin that will read potentiometer values
  int maxDeg;       // Maximum rotation of the potentiometer (degrees)
  int maxValue;     // Maximum raw output value of the potentiometer (usually is 1023)
};

#endif