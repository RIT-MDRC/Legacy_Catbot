#include "Motor.h"

Motor::Motor (int motorPin, int encoderPinA, int encoderPinB, int lowthresh, int highthresh)
  : Encoder(encoderPinA, encoderPinB), motorPin(motorPin), encoderPinA(encoderPinA), encoderPinB(encoderPinB) 
{
  counts = 0;
  Servo::attach(motorPin);
  arm();
  
  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);
  digitalWrite(encoderPinA, LOW);
  digitalWrite(encoderPinB, LOW);

  setMapLow(lowthresh);
  setMapHigh(highthresh);

} //construct Motor object

void Motor::Run(int speedPcnt, double timeSec) {
  arm();
  if (speedPcnt <= 100 && speedPcnt >= -100) {
    setSpeed(speedPcnt);
  }
  delay(timeSec * 1000);
  arm();
}//Run motor

void Motor::Run(int dir, int deg, int speedPcnt) {
  arm();
  
  int speed;
  int time;
  if (dir == 0) {
    speed = -1 * abs(speedPcnt);
  }
  else {
    speed = abs(speedPcnt);
  }
  //Implement conversion from desired degrees to speed+time given a certain speed*************
  //(do such that it doesnt depend on the delay - ie can run two commands at once)
  //***************************

  arm();
}//Run motor based on pos

void Motor::tuneESC(double low, double high) {
  
  {
  int angle = map(high, -100, 100, 0, 180);
  Servo::write(angle);
  
  delay(5000);

  angle = map(low, -100, 100, 0, 180); //Sets servo positions to different speeds
  Servo::write(angle);
  delay(5000);

  }
  
  /*//High forward
  int angle = map(high, -100, 100, 0, 180); //Sets servo positions to different speeds
  Servo::write(angle);
  delay(7000);

  //High reverse
  angle = map(low, -100, 100, 0, 180); //Sets servo positions to different speeds
  Servo::write(angle);
  delay(10000);*/
}//Setup ESC range


void Motor::readEncoder() {
  counts = this->Encoder::read();
}//Update counts var

int Motor::getDir() {
  volatile long preCounts = 0;
  readEncoder();
  preCounts = counts;
  delay(10);
  readEncoder();

  if(counts > preCounts){
    return -1; //CW / CCW (test)
  }
  else if(counts < preCounts){
    return 1; //CCW / CW
  }
  else{
    return 0; //Not moving
  }
  
}//Get direction of motor (-1 = CCW, 1 = CW, 0 = not moving)

int Motor::getVel() {

  return 0;
}//Get velocity feedback from encoder

long Motor::getCounts(){
  readEncoder();
  return counts;
}//Update counts var and return current counts value

void Motor::setSpeed(int speed) {
  int velocity = map(speed, -100, 100, mapLow, mapHigh); //Sets servo positions to different speeds ESC1.write(angle);
  //With full mapping [[map(speed, -100, 100, 0, 180)]], the max servo speeds are -88%->88%.

  Servo::writeMicroseconds(velocity);
}//Set motor speed and map

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

void Motor::printStatus(){
  String state = "Dir: " + String(getDir()) + " Vel: " + String(getVel()) + " Counts: " + String(getCounts());
  Serial.print(state);
}//Print motor state


//END OF MOTOR.CPP ****************************8
