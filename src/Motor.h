#ifndef Motor_h
#define Motor_h

#include "Arduino.h"
#include <Servo.h>
#include <math.h>
#include <string.h>

class Motor
{
  public:
    // Construct motor object
    Motor(int _motorPin, int _mapLow, int _mapHigh, int _mapMiddle);

    // Set motor speed to 0
    void arm();

    // Run motor at a percent speed for the given amount of time (in seconds).
    // A negative value for seconds will make the motor run infinitely.
    void run(int speedPercent, double seconds);

    // Set the low end of the motor speed mapping
    void setMapLow(double newLow);

    // Set the high end of the motor speed mapping
    void setMapHigh(double newHigh);
    
    // Get what the current lower mapping bound is
    double getMapLow();

    // Get what the current upper mapping bound is
    double getMapHigh();

  private:
    Servo esc;

    int motorPin;               // The pin that will send a signal to the motor

    double mapLow = 1000;       // Low end of motor speed mapping (max negative spin)
    double mapHigh = 2000;      // High end of motor speed mapping (max positive spin)
    double mapMiddle;           // Middle point of speed mapping (no spin)
};

#endif