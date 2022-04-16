#ifndef Motor_h
#define Motor_h

//Motor class for catbot hip joints
#include "Arduino.h"
#include <Servo.h>

static double mapLow = 10.8;
static double mapHigh = 169.2;

class Motor : public Servo {
  public:
    Motor(int motorPin, int encoderPinA, int encoderPinB); //construct motor object

    void Run(int speedPcnt, int timeSec); //Run motor for a % speed and a time in seconds

    void Run(int dir, int deg, int speedPcnt); //Run motor based on pos; dir = 0/1, 0=-% 1=+%

    void tuneESC(double low, double high); //Setup ESC range

    int getDir(); //Get directional feedback from encoder

    int getVel(); //Get velocity feedback from encoder

    

  private:
    int motorPin;
    int encoderPinA;
    int encoderPinB;

    void setSpeed(int speed);

    void arm();
    
};

#endif
