#include <Arduino.h>

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
#include "Motor.h"
//#include "Potentiometer.h"

#define LOWERLIMIT 900
#define MIDDLE 1500 // middle/starting value
#define UPPERLIMIT 2000

#define AMOTORPIN 13
#define BMOTORPIN 3

#define APOT A5
#define BPOT A4

#define STOP 1 // garbage value - enter in serial monitor to begin testing process
               // could and should be refined

// Motor motorB(BMOTORPIN, LOWERLIMIT, UPPERLIMIT, MIDDLE);


void setup()
{
  Motor motorA(AMOTORPIN, LOWERLIMIT, UPPERLIMIT, MIDDLE);
  Serial.begin(9600); // start serial at 9600 baud
  while (!Serial)
  {
  }
  delay(1000);
  Serial.write("starting program\n");
  delay(1000);
  // motorA.arm();
  motorA.run(40, 5);
}

void loop()
{
  Serial.write("running loop\n");

  delay(10);
}

// Servo firstESC;

// Motor motorB;
// Potentiometer potA(APOT, 285);
// Potentiometer potB(BPOT, 285);

// --- PROGRAM GRAVEYARD ---

// Serial.write("running loop\n");
// MOTORB.runCall(30);
// delay(2000);
// MOTORA.arm();
// MOTORB.arm();

// MOTORB.runCall(30);
// Serial.write("motorB Called");
// MOTORA.runCall(30);
// Serial.write("motorA Called");
// temp = Serial.parseInt();
// while (temp != STOP) {
//   Serial.write("work finished");
// }'
// MOTORB.arm();
// void setup(){
//  firstESC.attach(13);   //pin 13
//  firstESC.writeMicroseconds(MIDDLE);

//  for (int i = 0; i <= 3000; i += 100)
//  {
//   firstESC.writeMicroseconds(1800);
//   delay(100);
//  }

//  firstESC.writeMicroseconds(MIDDLE);
//  //set middle value ...........................
//   Serial.println("middlevalue");

//   firstESC.writeMicroseconds(MIDDLE);
//   Serial.println(MIDDLE);
//   while(value != START){        //wait until esc has been powered on
//     value = Serial.parseInt();
//     Serial.println("enter 3 to start");
//     delay(100);
//   }
// //.............................................

// //updown.......................................
//   for(int i=MIDDLE;i<=UPPERLIMIT;i+=20){
//     firstESC.writeMicroseconds(i);
//     Serial.println(i);
//     delay(100);
//   }
//   delay(2000); //pause at high thresh

//   for(int i=UPPERLIMIT;i>=LOWERLIMIT;i-=20){
//     firstESC.writeMicroseconds(i);
//     Serial.println(i);
//     delay(100);
//   }
//   delay(2000); //pause at low thresh

//   for(int i=LOWERLIMIT;i<=MIDDLE;i+=20){ //reset to middle position before entering manual mode
//     firstESC.writeMicroseconds(i);
//     Serial.println(i);
//     delay(100);
//   }
//   delay(1000);

//   value = MIDDLE;

//.........................
// }

// void loop(){
// enter write values manually in infinite loop

// temp = Serial.parseInt();

// if(temp>=1) //checking for invalid characters
// {
//  value = temp;
// }

/*
 if(temp == 'k')//killswitch
 {
  while(1)
  {
    firstESC.writeMicroseconds(MIDDLE);
    value = MIDDLE;
  }
 }*/

// Serial.println(value);   //user feedback
// firstESC.writeMicroseconds(value);
// }
