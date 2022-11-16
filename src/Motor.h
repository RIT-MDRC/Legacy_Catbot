#ifndef Motor_h
#define Motor_h

//Motor class for CatBot hip joints
#include "Arduino.h"
#include <Servo.h>
#include <math.h>
#include <String.h>

class Motor : public Servo{
  public:
    Motor(int motorPin, int encoderPinA, int encoderPinB, int lowthresh, int highthresh); //construct motor object, encoderPinA should be an interrupt Pin

    void arm(); //Set motor speed to 0

    void Run(int speedPcnt, double timeSec); //Run motor for a % speed and a time in seconds

    void setMapLow(double newLow); //Set the low end of the motor speed mapping

    void setMapHigh(double newHigh); //Set the high end of the motor speed mapping
    
    double getMapLow();

    double getMapHigh();


  private:
    int motorPin;
    int encoderPinA;
    int encoderPinB;

    double mapLow = 1000; //Low end of motor speed mapping
    double mapHigh = 2000; //High end of motor speed mapping
    
    volatile long counts; //Encoder Counts

    void setSpeed(int speed); //Set motor speed (low level control)
    
};

#endif
