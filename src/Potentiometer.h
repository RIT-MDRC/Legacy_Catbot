#ifndef Potentiometer_h
#define Potentiometer_h

// Potentiometer reader
// Written by: Dan and Hiro

class Potentiometer
{
public:
  Potentiometer(int _pin, int _maxDeg, int _maxValue = 800);

  // Converts raw data to a rotational degree value.
  // Starts at zero, and increases as potentiometer is rotated counterclockwise.
  int getReading();

  // Gets current degree reading as an integer value.
  int getReadingInt();

  int getRawReading();

  bool isInRawValue(int minRawVal, int maxRawVal);

  bool isInDegree(int minDeg, int maxDeg);

  bool isMoving(int tolerance = 1);

  bool isCloseToEdge(int tolerance = 50);

  bool isBottomHalf();

private:
  int pin;      // Pin that will read potentiometer values
  int maxDeg;   // Maximum rotation of the potentiometer (degrees)
  int maxValue; // Maximum raw output value of the potentiometer (usually is 1023)
  float lastRawReading;
};

#endif