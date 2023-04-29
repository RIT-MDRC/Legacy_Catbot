#ifndef Potentiometer_h
#define Potentiometer_h

// Potentiometer reader
// Written by: Dan and Hiro

class Potentiometer
{
public:
  Potentiometer(int _pin, int _maxDeg, int _minDeg = 0, int _minValue = 40, int _maxValue = 800);

  // Converts raw data to a rotational degree value.
  // Starts at zero, and increases as potentiometer is rotated counterclockwise.
  int getReading();

  // Gets current degree reading as an integer value.
  int getReadingInt();

  int getRawReading();

  bool inRawRange();

  bool inRawRange(int value);

  bool inDegRange();

  bool inDegRange(int value);

  bool inRawRange(int min, int max);

  bool inDegRange(int min, int max);

  bool inRange(int min, int max);

  bool inRange(int min, int max, int value);

  bool isMoving(int tolerance = 1);

  bool isCloseToEdge(int tolerance = 50);

  bool isBottomHalf();

  int getMinDegrees();

  int getMaxDegrees();

  int getCenterDegrees();

  bool readingApproximately(int target, float threshold);

private:
  int pin;    // Pin that will read potentiometer values
  int maxDeg; // Maximum rotation of the potentiometer (degrees)
  int minDeg; // Minimum rotation of the potentiometer (degrees)
  int centerDeg;
  int maxValue; // Maximum raw output value of the potentiometer (usually is 1023)
  int minValue;
  int centerValue;
  float lastRawReading;
};

#endif