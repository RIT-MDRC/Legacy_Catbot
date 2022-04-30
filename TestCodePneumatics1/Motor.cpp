#include "Motor.h"

Motor::Motor (int motorPin, int encoderPinA, int encoderPinB)
  : motorPin(motorPin), encoderPinA(encoderPinA), encoderPinB(encoderPinB) {
  counts = 0;
  attach(motorPin);
  arm();
  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);

  digitalWrite(encoderPinA, LOW);
  digitalWrite(encoderPinB, LOW);

  attachInterrupt(digitalPinToInterrupt(encoderPinA), readEncoder(), CHANGE);

} //construct motor object

void Motor::Run(int speedPcnt, int timeSec) {
  if (speedPcnt <= 100 && speedPcnt >= -100) {
    setSpeed(speedPcnt);
  }
  delay(timeSec * 1000);
}//Run motor

void Motor::Run(int dir, int deg, int speedPcnt) {
  int speed;
  int time;
  if (dir == 0) {
    speed = -1 * abs(speedPcnt);
  }
  else {
    speed = abs(speedPcnt);
  }
  //Implement conversion from desired degrees to speed+time given a certain speed*************
  //***************************

}//Run motor based on pos

void Motor::tuneESC(double low, double high) {
  //High forward
  int angle = map(99, -100, 100, low, high); //Sets servo positions to different speeds
  write(angle);
  delay(7000);

  //High reverse
  angle = map(-99, -100, 100, low, high); //Sets servo positions to different speeds
  write(angle);
  delay(10000);
}//Setup ESC range

//this function is triggered by the encoder CHANGE, and increments the encoder counter
void Motor::readEncoder() {
  if (digitalRead(encoderPinB) == digitalRead(encoderPinA))
  {
    counts = counts - 1; //you may need to redefine positive and negative directions
  }
  else
  {
    counts = counts + 1;
  }
} //End of Read encoder

int Motor::getDir() {

}//Get directional feedback from encoder

int Motor::getVel() {

}//Get velocity feedback from encoder

long Motor::getCounts(){
  return counts;
}

void Motor::setSpeed(int speed) {
  int angle = map(speed, -100, 100, mapLow, mapHigh); //Sets servo positions to different speeds ESC1.write(angle);
  //With full mapping [[map(speed, -100, 100, 0, 180)]], the max servo speeds are -88%->88%.

  write(angle);
}//Set motor speed and map

void Motor::arm() {
  setSpeed(0);
}
