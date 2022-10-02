#ifndef Motor_h
#define Motor_h

//Motor class for CatBot hip joints
#include "Arduino.h"
#include <Servo.h>
#include <Encoder.h> //Must install Encoder library from Arduino Library Manager
#include <math.h>
#include <String.h>

class Motor : public Servo, public Encoder{
  public:
    Motor(int motorPin, int encoderPinA, int encoderPinB); //construct motor object, encoderPinA should be an interrupt Pin

    void arm(); //Set motor speed to 0

    void Run(int speedPcnt, double timeSec); //Run motor for a % speed and a time in seconds

    void Run(int dir, int deg, int speedPcnt); //Run motor based on pos; dir = 0/1, 0=-% 1=+%

    void tuneESC(double low, double high); //Setup ESC range

    int getDir(); //Get directional feedback from encoder

    int getVel(); //Get velocity feedback from encoder

    long getCounts(); //Update and get value of counts

    void readEncoder(); //Update counts

    void setMapLow(double); //Set the low end of the motor speed mapping

    void setMapHigh(double); //Set the high end of the motor speed mapping

    double getMapLow();

    double getMapHigh();

    void printStatus(); //Print motor state

  private:
    int motorPin;
    int encoderPinA;
    int encoderPinB;

    double mapLow = 10.8; //Low end of motor speed mapping
    double mapHigh = 169.2; //High end of motor speed mapping
    
    volatile long counts; //Encoder Counts

    void setSpeed(int speed); //Set motor speed (low level control)
    
};

#endif
