#ifndef Motor_h
#define Motor_h

//Motor class for catbot hip joints
#include "Arduino.h"
#include <Servo.h>

class Motor {
  public:
    Motor(int motorPin,int escPin, int encoderPinA, int encoderPinB); //construct motor object
    void Run(int speedPcnt, int timeSec); //Run motor
    void Run(int dir, int deg, int speedPcnt); //Run motor based on pos
    int getDir(); //Get directional feedback from encoder
    int getVel(); //Get velocity feedback from encoder
    

    private:
    int motorPin;
    int escPin;
    int encoderPinA;
    int encoderPinB;
    void setspeed(Servo M, int speed);
    
};

#endif
