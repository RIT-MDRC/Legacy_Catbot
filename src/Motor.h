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

    // Run motor at a percent speed for the given amount of time (in seconds)
    void run(int speedPercent, double seconds);

    // Run motor at a percent speed for infinite amount of time
    void runCall(int speedPercent);

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

    int motorPin;

    double mapLow = 1000;       // Low end of motor speed mapping (max negative spin)
    double mapHigh = 2000;      // High end of motor speed mapping (max positive spin)
    double mapMiddle;           // Middle point of speed mapping (no spin)

   // void setSpeed(int speed);   // Set motor speed (low level control)
};

#endif