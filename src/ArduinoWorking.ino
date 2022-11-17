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
#include "Potentiometer.h"

// ----------------- CONSTANTS -------------------
// Motor constants
#define LOWERLIMIT 900
#define MIDDLE 1500 // middle/starting value
#define UPPERLIMIT 2000

#define AMOTORPIN 13
#define BMOTORPIN 3

// Potentiometer constants
#define APOT A5
#define BPOT A4

#define MAXDEG 285.00

// ----------------- GLOBAL VARIABLES -------------------
// Messing around with pointers because we are cool like that :D
Motor* aMotor = NULL;
Motor* bMotor = NULL;
Potentiometer* aPot = NULL;
Potentiometer* bPot = NULL;

// ----------------- MAIN FUNCTION ----------------------

void setup()
{
  // Defining every class for each component
  aMotor = new Motor(AMOTORPIN, LOWERLIMIT, UPPERLIMIT, MIDDLE);
  bMotor = new Motor(BMOTORPIN, LOWERLIMIT, UPPERLIMIT, MIDDLE);
  aPot = new Potentiometer(APOT, MAXDEG);
  bPot = new Potentiometer(BPOT, MAXDEG);

  Serial.begin(9600); // start serial at 9600 baud
  while (!Serial){}
  delay(1000);
  Serial.write("starting program\n");
  delay(1000);

  // ------------------ ACTUAL PROGRAM STARTS HERE ------------------
  // Reading angle from potentiometer
  float aDegree = aPot -> getReading();
  float bDegree = bPot -> getReading();
  Serial.println(aDegree);
  Serial.println(bDegree);

  // Waiting for both potentiometer to be rest to <5 degrees
  while ((!checkPot(aPot, 0.0, 1.0))||(!checkPot(bPot, 0.0, 1.0))){}

  // Calling both motors to spin indefinitely
  aMotor -> runCall(40);
  bMotor -> runCall(40);
  
  // Waiting for both potentiometers to be rotated > 30 degrees
  while ((!checkPot(aPot, 30.0, MAXDEG))||(!checkPot(bPot, 30.0, MAXDEG))){}

  // Calling both motors to stop
  aMotor -> arm();
  bMotor -> arm();

  // Make sure that the program has successfully ended before halting to prevent possible chance of memory leak
  end();
} // ---------------------- END OF PROGRAM -----------------------------

// LOOP FUNCTION AVOID IT AS MUCH AS POSSIBLE. ARDUINO COMPILER DOES NOT HANDLE THIS FILE WELL IG.
void loop()
{
  end();
  delay(100);
}

// ---------------------------------------------------------------------
// ---------------------- Helper methods below -------------------------
// ---------------------------------------------------------------------

void end(){
  // Runs the ending sequence to properly reset the pointers
  if (!aMotor || !bMotor || !aPot || !bPot) {
    Serial.write("Program succesfully ended.\n");
    return;
  }
  Serial.write("ending program...\n");
  delay(1000);
  delete aMotor;
  delete bMotor;
  delete aPot;
  delete bPot;
  aMotor = NULL;
  bMotor = NULL;
  aPot = NULL;
  bPot = NULL;
}

bool checkPot(Potentiometer* pot, float lowerRange, float upperRange){
  // Check function that check if the potentiometer is rotated to the correct degrees
  float reading = pot -> getReading();
  Serial.println("checking pot " + String(reading));
  bool lowerCheck = (lowerRange <= reading);
  bool upperCheck = (reading <= upperRange);
  return (lowerCheck && upperCheck);
}

