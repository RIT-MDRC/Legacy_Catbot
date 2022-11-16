#include "Motor.h"

/**
Code to iterate over range of speed values to test ESC limits and verify function

INSTRUCTIONS:
  1) Run Arduino code with ESC not powered
  2) Connect 12V supply to ESC
  3) Enter the START constant to serial monitor in order to begin testing
  4) Record Results
  5) Program enters manual mode - use the serial monitor to enter any speed value
*/

#include <Servo.h>

#define LOWERLIMIT 1000
#define MIDDLE 1500 // middle/starting value
#define UPPERLIMIT 2000

const int MAPin = 13;
const int MBPin = 12;
const int a1 = 1; // Motor A encoder Pin 1
const int a2 = 5; // Motor A encoder Pin 2

#define START 3 //garbage value - enter in serial monitor to begin testing process
                //could and should be refined

void setSpeed(int speed);
void Run(int speedPcnt, double timeSec);
void arm();

int value; 
int temp; //used to filter null characters


//Servo firstESC; 
Motor MA(MAPin, a1, a2, 1000, 2000);


void setup() {

 Serial.begin(9600);   // start serial at 9600 baud


  //firstESC.attach(MAPin);
  //arm();
  MA.arm();
 
  while(value != START){        //wait until esc has been powered on
    value = Serial.parseInt(); 
    Serial.println("enter 3 to start");
    delay(50);
  }

  value = 0;
}




void loop() {

//enter write values manually in infinite loop\
//USE PERCENTAGES +-100%

 temp = Serial.parseInt();
 /*
  if(temp == 'k')//killswitch
  {
    while(1)
    {
      firstESC.writeMicroseconds(MIDDLE);
      value = MIDDLE;
    }
  }*/

 
  if(temp!=0 && temp>=-100 && temp <=100) //checking for invalid characters
  {
    value = temp;
  }
 
 
  Serial.println(value);   //user feedback

  //Run(value,2);
  //MA.Run(value,2);
  
  
  delay(5000);
}

/*
void setSpeed(int speed) {
  int velocity = map(speed, -100, 100, LOWERLIMIT, UPPERLIMIT); //Sets servo positions to different speeds ESC1.write(angle);
  //With full mapping [[map(speed, -100, 100, 0, 180)]], the max servo speeds are -88%->88%.
  Serial.println(velocity); 
  firstESC.writeMicroseconds(velocity);
}//Set motor speed and map


void Run(int speedPcnt, double timeSec) {
  if (speedPcnt <= 100 && speedPcnt >= -100) {
    setSpeed(speedPcnt);
  }
  delay(timeSec * 1000);
  arm();
}

void arm() {
  setSpeed(0);
}//Set motor speed to 0
*/
