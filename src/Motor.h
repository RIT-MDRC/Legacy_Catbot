#ifndef Motor_h
#define Motor_h

#include "Arduino.h"
#include <Servo.h>
#include <math.h>
#include <string.h>
#include "Potentiometer.h"

class Motor
{
public:
  // Construct motor object
  Motor(int _motorPin, int _mapLow, int _mapHigh, int _mapMiddle, bool _resetMode);

  // Set motor speed to 0
  void arm();

  // Run motor at a percent speed for the given amount of time (in seconds)
  void run(int speedPercent, double seconds);

  // Run motor at a percent speed for infinite amount of time
  void runCall(int speedPercent);

  // Run motor at a raw value for the given amount of time (in seconds)
  void runRawValue(int value, double seconds);

  // Set the low end of the motor speed mapping
  void setMapLow(double newLow);

  // Set the high end of the motor speed mapping
  void setMapHigh(double newHigh);

  // Get what the current lower mapping bound is
  double getMapLow();

  // Get what the current upper mapping bound is
  double getMapHigh();

  // Stop the motor for a split second if we are running in the opposite direction
  void checkDirection(int speedPercent);

  // Update the current direction of the motor (speed can be in any unit except for raw esc value)
  void updateCurrentDirection(int speed);

  int reset(Potentiometer *pot);

  void runReverse(int speed);

  void moveAwayFromWall(Potentiometer *pot, int speed);

private:
  Servo esc;

  int motorPin;

  double mapLow = 1000;  // Low end of motor speed mapping (max negative spin)
  double mapHigh = 2000; // High end of motor speed mapping (max positive spin)
  double mapMiddle;      // Middle point of speed mapping (no spin)
  int currentDirection;  // Current direction of motor (1, 0, or -1)
  // void setSpeed(int speed);   // Set motor speed (low level control)
};

#endif