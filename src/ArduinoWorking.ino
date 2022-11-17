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

#define LOWERLIMIT 900
#define MIDDLE 1500 // middle/starting value
#define UPPERLIMIT 2000

#define START 3 //garbage value - enter in serial monitor to begin testing process
                //could and should be refined

int value = MIDDLE; 
int temp; //used to filter null characters


//Servo firstESC; 

void setup() {
 
 Motor motorA(13, LOWERLIMIT, UPPERLIMIT, MIDDLE); // Motor has to be initialized in setup() because  ?????? i don't know
 motorA.arm();

 Serial.begin(9600);   // start serial at 9600 baud
 while (!Serial) {}

 // Rotates kind of slowly one way for 3 seconds, then the other way
 motorA.run(15, 3);
 delay(200);
 motorA.run(-15, 3);
 
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
}




void loop() {

//enter write values manually in infinite loop

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
 
   //Serial.println(value);   //user feedback
   //firstESC.writeMicroseconds(value);
  
  delay(100);
}
