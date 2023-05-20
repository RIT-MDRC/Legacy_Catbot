#include <Arduino.h>
#include <Servo.h>
#include "Motor.h"
#include "Potentiometer.h"
#include "MotorController.h"

Servo ESC; // create servo object to control the ESC

int potValue;
long writeVal;
bool reset = false;
bool abductionAdductionAdjustment = true;
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

// leg side to side
#define MOTORPIN1 3
// leg forward and backwards (LE)
#define MOTORPIN2 5

#define LOWERLIMIT 900
#define MIDDLE 1450 // middle/starting value
#define UPPERLIMIT 2000

// -----------------------------
// -- POTENTIOMETER CONSTANTS --
// -----------------------------
// pin
#define APOTPIN A1
#define BPOTPIN A2

#define MAXDEG 285.00

// -------------------------
// -- Neumatics constants --
// -------------------------
// pins
#define COMPRESSORPIN 9
#define VALVE_1PIN 8
#define SENSORPIN A0        // Analog
#define COMP_SWITCHPIN 11   // button #1
#define VALVE1_SWITCHPIN 10 // button #2

#define VOLTAGE_CONST 5
#define P_MAX 145 // psi
#define P_MIN 0
#define SYSTEM_PRESSURE 82   // average pressure we want to maintain
#define PRESSURE_TOLERANCE 3 // tolerance for pressure (we want to maintain in the difference margin of 3 psi)

#define POT1_LOWER_BOUND (228)
#define POT1_CENTER (480.5)
#define POT1_UPPER_BOUND (733)

#define POT2_LOWER_BOUND (225)
#define POT2_CENTER (407.5)
#define POT2_UPPER_BOUND (590)

/// ------------------------
/// -- Setpoint constants --
/// ------------------------

#define SETPOINT_HIP_ABDUCT_DEGREES 8
#define SETPOINT_HIP_ADDUCT_DEGREES -8
#define SETPOINT_HIP_FLEX_DEGREES 20
#define SETPOINT_HIP_EXTEND_DEGREES -20

// ----------------- GLOBAL POINTERS --------------------
// ---- Pointers will be defined later in the setup -----
// ------------------------------------------------------
// Motor *motor1 = NULL;
// Motor *motor2 = NULL;
// Potentiometer *aPot = NULL;
// Potentiometer *bPot = NULL;

// This is the old motor 1 and pot A
MotorController *abductionAdduction = NULL;

// This is the old motor 2 and pot B
MotorController *flexionExtension = NULL;

Motor *motor1 = NULL;
// ----------------- MAIN FUNCTION ----------------------

void setup()
{
  setupPin();
  reset = false;
  Serial.begin(9600);
  while (!Serial)
  {
    if (isBothSwitchPressed())
    {
      reset = true;
    }
  };
  setMotorControllers(reset);
  while (!isBothSwitchPressed())
  {
    if (isCompSwitchPressed())
    {
      abductionAdductionAdjustment = false;
    }
    Serial.println("wait for esc to boot and press both buttons: " + String(reset) + " " + (abductionAdductionAdjustment ? "abdadd" : "flxext"));
  }
}

void loop()
{
  if (isBothSwitchPressed())
  {
    retractLeg(VALVE_1PIN, 5000);
    extendLeg(VALVE_1PIN, 5000);
  }
  else
  {
    mainPneumaticControl();
  }
  Serial.print("abductionAdduction:");
  Serial.print(abductionAdduction->getCurrentDegree());
  Serial.print(",flexionExtension:");
  Serial.println(flexionExtension->getCurrentDegree());
  delay(100);
}

// // if (reset)
// // {
// //   // Serial.println("resetting motors");
// //   // MotorController *mc = abductionAdductionAdjustment ? abductionAdduction : flexionExtension;
// //   // mc->printPotLocationInLoop();
// // }

// while (true)
// {
//   // Serial.println("abduction hip");
//   // abductHip();
//   // Serial.println("adduction hip");
//   // adductHip();
//   // delay(1000);

//   // Serial.println("Flex hip");
//   // flexHip();
//   // Serial.println("Extend hip");
//   // extendHip();
//   // delay(1000);

//   mainPneumaticControl();

//   Serial.println("retract");
//   retractLeg(VALVE_1PIN, 3);
//   Serial.println("extend");
//   extendLeg(VALVE_1PIN, 3);
//   delay(1000);
// }

// while (true)
// {
//   abductionAdduction->stop();
//   flexionExtension->stop();
// };
// if (isBothSwitchPressed())
// { // Run Motor program if push both buttons at the same time
//   // delay(500);
//   // extendLeg(VALVE_1PIN, 1);
//   // stepForward(VALVE_1PIN, motor2, 20, 3);
//   // slowStep(VALVE_1PIN, motor2, 20, 4, 1);
//   // sideToside(motor1, 20, 3, 1);
// }
// else
// { // Pneumatics Control
//   mainPneumaticControl();
// }

// while (true)
//   ;

// ----------------------------------------------------------------------
// ---------------------- Setup Functions below -------------------------
// ----------------------------------------------------------------------

void setMotorControllers(bool resetMode)
{
  Motor *aaMotor = new Motor(MOTORPIN1, LOWERLIMIT, UPPERLIMIT, MIDDLE, resetMode);
  Motor *feMotor = new Motor(MOTORPIN2, LOWERLIMIT, UPPERLIMIT, MIDDLE, resetMode);

  Potentiometer *aaPot = new Potentiometer(APOTPIN, MAXDEG);
  Potentiometer *fePot = new Potentiometer(BPOTPIN, MAXDEG);

  abductionAdduction = new MotorController(aaMotor, aaPot);
  flexionExtension = new MotorController(feMotor, fePot);
}

void setupPin()
{
  // Setup Arduino pins for pneumatics
  pinMode(COMPRESSORPIN, OUTPUT);
  pinMode(VALVE_1PIN, OUTPUT);

  pinMode(SENSORPIN, INPUT);
  pinMode(COMP_SWITCHPIN, INPUT);
  pinMode(VALVE1_SWITCHPIN, INPUT);

  // Set relay pins to low (relay is ACTIVE HIGH)
  digitalWrite(COMPRESSORPIN, LOW);
  digitalWrite(VALVE_1PIN, LOW);
};

/**
 * This is the esc setup function for just testing the esc controlling method
 */
// void setupEsc(int pin)
// {
//   ESC.attach(pin);
// }

bool isBothSwitchPressed()
{
  return (digitalRead(COMP_SWITCHPIN) == HIGH) && (digitalRead(VALVE1_SWITCHPIN) == HIGH);
}

bool isCompSwitchPressed()
{
  return digitalRead(COMP_SWITCHPIN) == HIGH;
}

void mainPneumaticControl()
{
  double sensorRead = (analogRead(SENSORPIN) * 0.0049);                                                              // Volts
  double pressure = (((sensorRead - 0.1 * VOLTAGE_CONST) * (P_MAX - P_MIN)) / (0.8 * VOLTAGE_CONST)) + P_MIN + 0.36; // PSI

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

// ===========================================================
// ================ Step Sequence Functions ==================
// ===========================================================

// void abductHip()
// {
//   abductionAdduction->turnTo(SETPOINT_HIP_ABDUCT_DEGREES);
// }

// void adductHip()
// {
//   abductionAdduction->turnTo(SETPOINT_HIP_ABDUCT_DEGREES);
// }

// void flexHip()
// {
//   flexionExtension->turnTo(SETPOINT_HIP_FLEX_DEGREES);
// }

// void extendHip()
// {
//   flexionExtension->turnTo(SETPOINT_HIP_EXTEND_DEGREES);
// }

// Extends the leg by calling the pneumatics
void extendLeg(int valve, float durationSec)
{
  digitalWrite(valve, LOW);
  delay(durationSec);
}

void retractLeg(int valve, float durationSec)
{
  digitalWrite(valve, HIGH);
  delay(durationSec);
}

// ===========================================================
// ================ Test Functions ===========================
// ===========================================================

void end()
{
  // Runs the ending sequence to properly reset the pointers
  if (!abductionAdduction || !flexionExtension)
  {
    Serial.write("Program succesfully ended.\n");
    return;
  }
  Serial.write("ending program...\n");
  delay(1000);
  delete abductionAdduction;
  delete flexionExtension;
  abductionAdduction = NULL;
  flexionExtension = NULL;
}

void resetMotors()
{
  // motor1->runRawValue(MIDDLE, 3);
  // motor2->runRawValue(MIDDLE, 3);
}

/**
 * This is a function to run the esc with a potentiometer directly
 */
void runEsc(Motor *motor, Potentiometer *pot)
{
  potValue = pot->getRawReading(); // reads the value of the potentiometer (value between 0 and 1023)
  if (potValue != 0)
  {
    Serial.println(potValue); // Output the value to the serial monitor
  }
  potValue = map(potValue, 0, 840, -100, 100); // scale it to use it with the servo library (value between 0 and 180)
  motor->runCall(potValue);                    // Send the signal to the ESC
}

/**
 * This is the function to test the esc with multiple speed values
 */
void multiStageMotorTest(Motor *motor, bool positive)
{
  Serial.println("Testing Motor");
  Serial.println("testing arm function");
  Serial.println("Motor should be not running");
  motor->runRawValue(MIDDLE, 3);
  Serial.println("ending arm function");
  delay(1000);
  Serial.println("testing out negative direction");
  int positiveNum = positive ? 1 : -1;
  for (int i = 0; i < 10; i++)
  {
    int vel = map(positiveNum * i * 10, -100, 0, LOWERLIMIT, MIDDLE);
    Serial.println(positiveNum * i * 10);
    Serial.println(vel);
    motor->run(positiveNum * i * 10, 3);
    delay(500);
  }
  delay(1000);
}

/**
 * This is the function to test the esc with a single speed value
 */
void singleSpeedMotorTest(Motor *motor, int motorSpeedPercent)
{
  Serial.println("Testing Motor: raw value - " + String(motorSpeedPercent));
  delay(1000);
  motor->runRawValue(motorSpeedPercent, 1);
}