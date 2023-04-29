#ifndef MotorController_h
#define MotorController_h

#include "Arduino.h"
#include <Servo.h>
#include <Potentiometer.h>
#include <Motor.h>
#include <math.h>
#include <string.h>

class MotorController
{
public:
  // Construct motor object
  MotorController(Motor *_motor, Potentiometer *_pot);

  // Calibrate the potentiometer
  void calibrate();

  // Stop Motor
  void stop();

  // Turn motor by the amount of degrees with a given speed
  void turn(int degree, int speedPercent);

  // Turn motor by the amount of degrees with default speed
  void turn(int degree);

  // Turn the motor to a specific degree with a default speed
  void turnTo(int degree);

  // Turn the motor to a specific degree with a given speed
  void turnTo(int degree, int speedPercent);

  // Turn the motor to a specific degree with in a given time
  void turnToWithin(int degree, int time);

  int getCurrentDegree();

  int getMinDegrees();

  int getMaxDegrees();

  int getDistanceToMax();

  int getDistanceToMin();

  int getDegreesToClosest();

  int getDirectionToClosest();

  int getDirectionToFarthest();

  int getDirectionToMax();

  int getDirectionToMin();

  void printPotLocationInLoop(int delayTime = 100);

  bool isAtSetpoint(double setpoint, int direction);

private:
  Motor *motor;
  Potentiometer *pot;

  int defaultSpeed = 70;         // Default speed of motor
  int potOffset = 0;             // Offset of potentiometer
  double speedDegreeRatio = 0.5; // Ratio of speed to degrees
};

#endif