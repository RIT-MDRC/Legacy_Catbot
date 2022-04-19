#include <Servo.h>
#include "Motor.h"

//System Constants for Sensor Calculation
const int V_SENSOR = 5;
const int P_MAX = 145; //psi
const int P_MIN = 0;
const int SYSTEM_PRESSURE = 82;
const int PRESSURE_TOLERANCE = 3;
///////////////////////////////////////////////////////////////////////////////////////////////

//Arduino Uno Pins System Pins
const int COMPRESSOR = 3;
const int VALVE_1 = 2;
const int SENSOR = A0;  //Analog
const int COMP_SWITCH = 5;
const int VALVE1_SWITCH = 4;
///////////////////////////////////////////////////////////////////////////////////////////////

//Motor Declarations
Servo MA; //HAA
Servo MB; //HFE
///////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(9600);

  //Setup Arduino pins
  pinMode(COMPRESSOR, OUTPUT);
  pinMode(VALVE_1, OUTPUT);
  //pinMode(ESCA, OUTPUT);
  //pinMode(ESCB, OUTPUT);
  
  pinMode(SENSOR, INPUT);
  pinMode(COMP_SWITCH, INPUT);
  pinMode(VALVE1_SWITCH, INPUT);

  //Motor Control Pins
  MA.attach(9); //ESCA
  MB.attach(8); //ESCB

  //Set relay pins to low (relay is ACTIVE HIGH)
  digitalWrite(COMPRESSOR, LOW);
  digitalWrite(VALVE_1, LOW);

  arm(MA);  //Set ESCs to 0
  arm(MB);

} //End of Program Setup

void loop() { //Main Program
///////////////////////////////////////////////////////////////////////////////////////////////
  //Read in and calculate the pressure from the analog pressure sensor (psi)
  double sensorRead = (analogRead(SENSOR) * 0.0049); //Volts
  double pressure = (((sensorRead - 0.1*V_SENSOR)*(P_MAX - P_MIN))/(0.8*V_SENSOR)) + P_MIN + 0.72; //PSI

  //Print out readings
  Serial.print("Pressure: ");
  Serial.print(sensorRead);
  Serial.print("  ...  ");
  Serial.print(pressure);
  Serial.print(" psi, CSwitch: "); 
  Serial.print(digitalRead(COMP_SWITCH)); 
  Serial.print(", VSwitch: "); 
  Serial.println(digitalRead(VALVE1_SWITCH));

  
 // pressure = SYSTEM_PRESSURE + 1; //Comment out for Automatic Compressor operation
///////////////////////////////////////////////////////////////////////////////////////////////  
  setSpeed(MA,0); //Set speed to 0
  setSpeed(MB,0);

//Control  
  if((digitalRead(COMP_SWITCH) == HIGH) && (digitalRead(VALVE1_SWITCH) == HIGH)){ //Run Motor program if push both buttons at the same time
    delay(100);
    //A = HAA, B = HFE
    
    //setupESC(MA);
    //setupESC(MB);
    
    //runESCTest(MB);
    //runESCTest(MA);

    //runTwoESC(MB, MA);

    runImagine22(MA, MB, VALVE_1);
    
    
    delay(100);
  }
  else{ //Pneumatics Control
///
    if(pressure > SYSTEM_PRESSURE){   //First check if system pressure is too high, turn off compressor
      digitalWrite(COMPRESSOR, LOW);
    }
 
    if(((SYSTEM_PRESSURE - pressure) > PRESSURE_TOLERANCE) || ((digitalRead(COMP_SWITCH) == HIGH)&&(digitalRead(VALVE1_SWITCH) == LOW))){   //If pressure is too low, or overriden by manual switch, turn on compressor
      digitalWrite(COMPRESSOR, HIGH);
    }
    else{
      digitalWrite(COMPRESSOR, LOW);
    }
///
    if(digitalRead(VALVE1_SWITCH) == HIGH){   //If valve switch is pressed open valve
      digitalWrite(VALVE_1, HIGH);
    }
    else{
      digitalWrite(VALVE_1, LOW);
    }
  }
  
  delay(100);
} //End of main program
///////////////////////////////////////////////////////////////////////////////////////////////

//write(-100) = Full backwards
//write(100) = Full forwards
void runESCTest(Servo M){ //Run Motor test code
  setSpeed(M, 20);
  delay(1200);

  setSpeed(M, 0);
  delay(1000);
  
  setSpeed(M, -20);
  delay(1200);
  
  setSpeed(M, 0);
  delay(1000); //Turns off for 1 second

 } //End of ESC Test program
 ///////////////////////////////////////////////////////////////////////////////////////////////
 
void setupESC(Servo M){ //Run setup code to normalize ESC input ranges
  setSpeed(M, 99);  //High forward
  delay(7000);

  setSpeed(M, -99); //High reverse
  delay(10000);

 } //End of ESC Setup
///////////////////////////////////////////////////////////////////////////////////////////////
void runTwoESC(Servo M1, Servo M2){ //Sample test for both motors at same time
  setSpeed(M1, 20);
  delay(1500);

  setSpeed(M1, 0);
  setSpeed(M2, 20);
  delay(1000);
  
  setSpeed(M2, 0);
  setSpeed(M1, -20);
  delay(1500);

  setSpeed(M1, 0);
  setSpeed(M2, -20);
  delay(1000);
  
  setSpeed(M1, 0);
  setSpeed(M2, 0);
  delay(1000); //Turns off for 1 second
  
}//Run both ESC tests
///////////////////////////////////////////////////////////////////////////////////////////////

void arm(Servo M){  //Set motor speed to 0

  setSpeed(M,0); //Sets speed variable delay(1000);

}
///////////////////////////////////////////////////////////////////////////////////////////////

void setSpeed(Servo M, int speed){ //Set the speed for motor from -100% to 100%

  int angle = map(speed, -100, 100, 10.8, 169.2); //Sets servo positions to different speeds ESC1.write(angle);
  //With full mapping [[map(speed, -100, 100, 0, 180)]], the max servo speeds are -88%->88%.
  
  M.write(angle);
}

///////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////IMAGINE RIT DEMO CODE//////////////////////////////////////////
//////////////////////////////////By Devon and Sammi///////////////////////////////////////////
///////////////////////////////////////4/23/22/////////////////////////////////////////////////
    
    // Goal: run A and B 
    // HAA is out  and HFE is rotate
    // order of function , what happens first
    // angel - speed and time still set values 
    // Inflate up, out deflate down
    
void runImagine22(Servo MA, Servo MB, int VALVE){
  //MA = HAA, MB = HFE, VALVE = Muscle Control Signal
  //For motors, Stay in [-20,20]. 0 = Stop. Positions are related to speed and time on.
  //Gear reduction = 100:1.
  //Will likely be able to only trigger muscle once without refilling reservoir

  digitalWrite(VALVE, HIGH);            //inflates valve
 
 setSpeed(MB,20);
 setSpeed (MA,0);
  delay(2000);

  setSpeed(MB,0);
  setSpeed(MA,10);
    delay(2000);

  setSpeed(MB,-20);
  setSpeed(MA,0);
    delay(2000);

  setSpeed(MB,0);
  setSpeed(MA,-9); 
    delay(500); //Wait for 500ms

  digitalWrite(VALVE, LOW);     //Releases 
  
} //End of Imagine 2022 Demo Program
