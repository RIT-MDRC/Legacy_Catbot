#include "Motor.h"

//System Constants for Sensor Calculation
const int V_SENSOR = 5;
const int P_MAX = 145; //psi
const int P_MIN = 0;
const int SYSTEM_PRESSURE = 82;
const int PRESSURE_TOLERANCE = 3;
///////////////////////////////////////////////////////////////////////////////////////////////
//Arduino Leonardo System Pins
const int COMPRESSOR = 9;
const int VALVE_1 = 8;
const int SENSOR = A0;  //Analog
const int COMP_SWITCH = 11;
const int VALVE1_SWITCH = 10;
///////////////////////////////////////////////////////////////////////////////////////////////
//Encoder Pins and Vars
const int a1 = 1; //Motor A encoder Pin 1
const int a2 = 5; //Motor A encoder Pin 2
const int b1 = 0; //Motor B encoder Pin 1
const int b2 = 4;  //Motor B encoder Pin 2
///////////////////////////////////////////////////////////////////////////////////////////////
//Motor Controller pins
const int MAPin = 13;
const int MBPin = 12;

//Motor Declarations
Motor MA(MAPin, a1, a2); //HAA
Motor MB(MBPin, b1, b2); //HFE
///////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(115200);
  interrupts(); //Enable interrupts for encoders

  //Setup Arduino pins
  pinMode(COMPRESSOR, OUTPUT);
  pinMode(VALVE_1, OUTPUT);

  pinMode(SENSOR, INPUT);
  pinMode(COMP_SWITCH, INPUT);
  pinMode(VALVE1_SWITCH, INPUT);

  //Set relay pins to low (relay is ACTIVE HIGH)
  digitalWrite(COMPRESSOR, LOW);
  digitalWrite(VALVE_1, LOW);

} //End of Program Setup

void loop() { //Main Program
  //////////////////////////////////////////////////////////////////////////////////////////////
  //Read in and calculate the pressure from the analog pressure sensor (psi)
  double sensorRead = (analogRead(SENSOR) * 0.0049); //Volts
  double pressure = (((sensorRead - 0.1 * V_SENSOR) * (P_MAX - P_MIN)) / (0.8 * V_SENSOR)) + P_MIN + 0.36; //PSI

  //Print out readings
  Serial.print("Pressure: ");
  Serial.print(sensorRead);
  Serial.print("  ...  ");
  Serial.print(pressure);
  Serial.print(" psi, CSwitch: ");
  Serial.print(digitalRead(COMP_SWITCH));
  Serial.print(", VSwitch: ");
  Serial.print(digitalRead(VALVE1_SWITCH));
  Serial.print("|| MA: "); MA.printStatus();
  Serial.print("|| MB: "); MB.printStatus();
  Serial.println();

  // pressure = SYSTEM_PRESSURE + 1; //Comment out for Automatic Compressor operation
  //////////////////////////////////////////////////////////////////////////////////////////////

  //Control
  if ((digitalRead(COMP_SWITCH) == HIGH) && (digitalRead(VALVE1_SWITCH) == HIGH)) { //Run Motor program if push both buttons at the same time
    delay(100);
    //A = HAA, B = HFE

   //Tune range for ESCs syntax:(high forward, high reverse)
    MA.tuneESC(-86, 99);
    //MB.tuneESC(-86,99);

   //Set new map ranges
    //MA.setMapLow(-86);
    //MA.setMapHigh(99);
    //MB.setMapLow(-86);
    //MB.setMapHigh(99);

   //Program to move motor by a small amount (for resetting)
    //MA.Run(20, 0.25); //HAA
    //MB.Run(20, 0.25); //HFE
    
   //runImagine22(MA, MB, VALVE_1);
  }
  //////////////////////////////////////////////////////////////////////////////////////////////
  else { //Pneumatics Control
    if (pressure > SYSTEM_PRESSURE) { //First check if system pressure is too high, turn off compressor
      digitalWrite(COMPRESSOR, LOW);
    }

    if (((SYSTEM_PRESSURE - pressure) > PRESSURE_TOLERANCE) || ((digitalRead(COMP_SWITCH) == HIGH) && (digitalRead(VALVE1_SWITCH) == LOW))) {
      //If pressure is too low, or overriden by manual switch, turn on compressor
      digitalWrite(COMPRESSOR, HIGH);
    }
    else {
      digitalWrite(COMPRESSOR, LOW);
    }
    
    if ((digitalRead(COMP_SWITCH) == LOW) && (digitalRead(VALVE1_SWITCH) == HIGH)) { //If valve switch is pressed open valve
      digitalWrite(VALVE_1, HIGH);
    }
    else {
      digitalWrite(VALVE_1, LOW);
    }
  }
  
  delay(100);
} //End of main program


///////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////IMAGINE RIT DEMO CODE//////////////////////////////////////////
//////////////////////////////////By Devon and Sammi///////////////////////////////////////////
///////////////////////////////////////4/23/22/////////////////////////////////////////////////
// Goal: run A and B
// HAA is out  and HFE is rotate
// order of function , what happens first
// angel - speed and time still set values
// Inflate up, out deflate down

void runImagine22(Motor MA, Motor MB, int VALVE) {
  //MA = HAA, MB = HFE, VALVE = Muscle Control Signal
  //For motors, Stay in [-20,20]. 0 = Stop. Positions are related to speed and time on.
  //Gear reduction = 100:1.
  //Will likely be able to only trigger muscle once without refilling reservoir

  MA.arm();
  MB.arm();
  
  digitalWrite(VALVE, HIGH);            //inflates valve
  
  MB.Run(20, 0.75);
  MA.Run(10, 1);
  MB.Run(-20, 2);
  MA.Run(-9, 0.5);

  digitalWrite(VALVE, LOW);     //Releases
  
  MA.arm();
  MB.arm();

  /*Previous program (before 5/2022 revisions)
   * digitalWrite(VALVE, HIGH);
   * setSpeed(MB, 20);
   * setSpeed (MA, 0);
   * delay(750);

   * setSpeed(MB, 0);
   * setSpeed(MA, 10);
   * delay(1000);

   * setSpeed(MB, -20);
   * setSpeed(MA, 0);
   * delay(2000);

   * setSpeed(MB, 0);
   * setSpeed(MA, -9);
   * delay(500); //Wait for 500ms
   * digitalWrite(VALVE, LOW);     //Releases
   */
  
} //End of Imagine 2022 Demo Program
