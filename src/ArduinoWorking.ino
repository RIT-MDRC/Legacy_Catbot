#include <Arduino.h>
#include <Servo.h>
#include "Motor.h"
#include "Potentiometer.h"
/**
Code to iterate over range of speed values to test ESC limits and verify function

INSTRUCTIONS:
  1) Run Arduino code with ESC not powered
  2) Connect 12V supply to ESC
  3) Enter the START constant to serial monitor in order to begin testing
  4) Record Results
  5) Program enters manual mode - use the serial monitor to enter any speed value
*/


// ----------------- CONSTANTS -------------------

// ---------------------
// -- MOTOR CONSTANTS --
// ---------------------
// pin
#define AMOTORPIN 13
#define BMOTORPIN 3

#define LOWERLIMIT 900
#define MIDDLE 1500 // middle/starting value
#define UPPERLIMIT 2000

// -----------------------------
// -- POTENTIOMETER CONSTANTS --
// -----------------------------
// pin
#define APOTPIN A5
#define BPOTPIN A4

#define MAXDEG 285.00

// -------------------------
// -- Neumatics constants --
// -------------------------
// pins
#define COMPRESSORPIN 9
#define VALVE_1PIN 8
#define SENSORPIN A0 // Analog
#define COMP_SWITCHPIN 11
#define VALVE1_SWITCHPIN 10

#define V_SENSOR 5
#define P_MAX 145 // psi
#define P_MIN 0
#define SYSTEM_PRESSURE 82
#define PRESSURE_TOLERANCE 3

// ----------------- GLOBAL POINTERS --------------------
// ---- Pointers will be defined later in the setup -----
// ------------------------------------------------------
Motor *aMotor = NULL;
Motor *bMotor = NULL;
Potentiometer *aPot = NULL;
Potentiometer *bPot = NULL;

// ----------------- MAIN FUNCTION ----------------------

void setup()
{
  // Defining every class for each component
  aMotor = new Motor(AMOTORPIN, LOWERLIMIT, UPPERLIMIT, MIDDLE);
  bMotor = new Motor(BMOTORPIN, LOWERLIMIT, UPPERLIMIT, MIDDLE);
  aPot = new Potentiometer(APOTPIN, MAXDEG);
  bPot = new Potentiometer(BPOTPIN, MAXDEG);

  Serial.begin(9600); // start serial at 9600 baud
  while (!Serial)
  {
  }
  delay(1000);
  Serial.write("starting program\n");
  delay(1000);

  // Setup Arduino pins for pneumatics
  pinMode(COMPRESSORPIN, OUTPUT);
  pinMode(VALVE_1PIN, OUTPUT);

  pinMode(SENSORPIN, INPUT);
  pinMode(COMP_SWITCHPIN, INPUT);
  pinMode(VALVE1_SWITCHPIN, INPUT);

  // Set relay pins to low (relay is ACTIVE HIGH)
  digitalWrite(COMPRESSORPIN, LOW);
  digitalWrite(VALVE_1PIN, LOW);

  // -------------------------------------------------------------------
  // ------------------ ACTUAL PROGRAM STARTS HERE ---------------------
  // -------------------------------------------------------------------
  // Reading angle from potentiometer
  float aDegree = aPot->getReading();
  float bDegree = bPot->getReading();
  Serial.println(aDegree);
  Serial.println(bDegree);

  // Calling both motors to spin indefinitely
  aMotor->runCall(40);
  bMotor->runCall(40);

  delay(2000);

  // Waiting for both potentiometers to be rotated > 30 degrees
  while ((!checkPot(aPot, 30.0, MAXDEG)) || (!checkPot(bPot, 30.0, MAXDEG)))
  {
  }

  // Calling both motors to stop
  aMotor->arm();
  bMotor->arm();
}

void loop()
{
  //////////////////////////////////////////////////////////////////////////////////////////////
  // Read in and calculate the pressure from the analog pressure sensor (psi)
  double sensorRead = (analogRead(SENSORPIN) * 0.0049);                                                    // Volts
  double pressure = (((sensorRead - 0.1 * V_SENSOR) * (P_MAX - P_MIN)) / (0.8 * V_SENSOR)) + P_MIN + 0.36; // PSI

  // Print out readings
  Serial.print("Pressure: ");
  Serial.print(sensorRead);
  Serial.print("  ...  ");
  Serial.print(pressure);
  Serial.print(" psi, CSwitch: ");
  Serial.print(digitalRead(COMP_SWITCHPIN));
  Serial.print(", VSwitch: ");
  Serial.print(digitalRead(VALVE1_SWITCHPIN));
  Serial.println();

  // pressure = SYSTEM_PRESSURE + 1; //Comment out for Automatic Compressor operation
  //////////////////////////////////////////////////////////////////////////////////////////////

  // Control
  if ((digitalRead(COMP_SWITCHPIN) == HIGH) && (digitalRead(VALVE1_SWITCHPIN) == HIGH))
  { // Run Motor program if push both buttons at the same time
    delay(500);
    // extendLeg(VALVE_1PIN);
    stepForward(VALVE_1PIN, aMotor, 20, 3);
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////

  else
  { // Pneumatics Control
    if (pressure > SYSTEM_PRESSURE)
    { // First check if system pressure is too high, turn off compressor
      digitalWrite(COMPRESSORPIN, LOW);
    }

    if (((SYSTEM_PRESSURE - pressure) > PRESSURE_TOLERANCE) || ((digitalRead(COMP_SWITCHPIN) == HIGH) && (digitalRead(VALVE1_SWITCHPIN) == LOW)))
    {
      // If pressure is too low, or overriden by manual switch, turn on compressor
      digitalWrite(COMPRESSORPIN, HIGH);
    }
    else
    {
      digitalWrite(COMPRESSORPIN, LOW);
    }

    if ((digitalRead(COMP_SWITCHPIN) == LOW) && (digitalRead(VALVE1_SWITCHPIN) == HIGH))
    { // If valve switch is pressed open valve
      digitalWrite(VALVE_1PIN, HIGH);
    }
    else
    {
      digitalWrite(VALVE_1PIN, LOW);
    }
  }

  delay(100);
}

// ---------------------------------------------------------------------
// ---------------------- Helper methods below -------------------------
// ---------------------------------------------------------------------

void extendLeg(int valve, float durationSec)
  // Extends the leg by calling the pneumatics
{
  digitalWrite(valve, HIGH);
  delay(durationSec);
}

void retractLeg(int valve, float durationSec)
  // Retract the leg by calling the pneumatics
{
  digitalWrite(valve, LOW);
  delay(durationSec);
}

void rotateLegForward(Motor *motor, int rotationSpeedPer, float durationSec)
{
  // Rotate the motor to simulate the leg moving forward
  motor->run(rotationSpeedPer, durationSec);
}

void rotateLegBackward(Motor *motor, int rotationSpeedPer, float durationSec)
{
  // Rotate the motor the opposite way to simulate the leg pushing the ground backward
  motor->run(-rotationSpeedPer, durationSec);
}

void legLiftForward(int valve, Motor *motor, int rotationSpeedPer, float durationSec)
{
  // Sequence to Lift the leg and moving it forward
  retractLeg(valve, durationSec / 2);
  rotateLegForward(motor, rotationSpeedPer , durationSec / 2);
}

void legDropBackward(int valve, Motor *motor, int rotationSpeedPer, float durationSec)
{
  // Sequence to step down and push itself forward
  extendLeg(valve, durationSec / 2);
  rotateLegBackward(motor, rotationSpeedPer, durationSec / 2);
}

void stepForward(int valve, Motor *motor, int rotationSpeedPer, float durationSec)
{
  // Sequence to make a step forward
  delay(durationSec / 6);
  legLiftForward(valve, motor, rotationSpeedPer, durationSec/3);
  delay(durationSec / 6);
  legDropBackward(valve, motor, rotationSpeedPer, durationSec/3);
}

void end()
{
  // Runs the ending sequence to properly reset the pointers
  if (!aMotor || !bMotor || !aPot || !bPot)
  {
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

bool checkPot(Potentiometer *pot, float lowerRange, float upperRange)
{
  // Check function that check if the potentiometer is rotated to the correct degrees
  float reading = pot->getReading();
  Serial.println("checking pot " + String(reading));
  bool lowerCheck = (lowerRange <= reading);
  bool upperCheck = (reading <= upperRange);
  return (lowerCheck && upperCheck);
}