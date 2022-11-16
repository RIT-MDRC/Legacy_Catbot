#include "Motor.h"

Motor::Motor (int motorPin, int encoderPinA, int encoderPinB, int lowthresh, int highthresh)
  : motorPin(motorPin), encoderPinA(encoderPinA), encoderPinB(encoderPinB), mapLow(lowthresh), mapHigh(highthresh)
{
  Servo::attach(motorPin);
  
  //pinMode(encoderPinA, INPUT);
  //pinMode(encoderPinB, INPUT);
  //digitalWrite(encoderPinA, LOW);
  //digitalWrite(encoderPinB, LOW);

  //setMapLow(lowthresh);
  //setMapHigh(highthresh);
  //arm();

} //construct Motor object



void Motor::Run(int speedPcnt, double timeSec) {
  //arm();
  if (speedPcnt <= 100 && speedPcnt >= -100) {
    setSpeed(speedPcnt);
  }
  delay(timeSec * 1000);
  arm();
}//Run motor

void Motor::arm() {
  setSpeed(0);
}//Set motor speed to 0

void Motor::setMapLow(double newLow){
  mapLow = newLow;
}//Set the low end of the motor speed mapping

void Motor::setMapHigh(double newHigh){
  mapHigh = newHigh;
}//Set the high end of the motor speed mapping

double Motor::getMapLow(){
  return mapLow;
}//Get mapLow

double Motor::getMapHigh(){
  return mapHigh;
}//Get mapHigh



void Motor::setSpeed(int speed) {
  int velocity = map(speed, -100, 100, mapLow, mapHigh); //Sets servo positions to different speeds ESC1.write(angle);
  //With full mapping [[map(speed, -100, 100, 0, 180)]], the max servo speeds are -88%->88%.
  Serial.println(velocity);
  Servo::writeMicroseconds(velocity);
}//Set motor speed and map



//END OF MOTOR.CPP ****************************8
