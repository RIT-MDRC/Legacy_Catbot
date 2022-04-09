#include <Servo.h>

//System Constants for Sensor Calculation
const int V_SENSOR = 5;
const int P_MAX = 145; //psi
const int P_MIN = 0;
const int SYSTEM_PRESSURE = 70;
///////////////////////////////////////////////////////////////////////////////////////////////

//Arduino Uno Pins
const int COMPRESSOR = 3;
const int VALVE_1 = 2;
const int SENSOR = A0;  //Analog
const int COMP_SWITCH = 5;
const int VALVE1_SWITCH = 4;
const int ESCA = 6;
const int ESCB = 7;
///////////////////////////////////////////////////////////////////////////////////////////////

//Motor Declarations
Servo MA;
Servo MB;
///////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(9600);

  //Setup pins
  pinMode(COMPRESSOR, OUTPUT);
  pinMode(VALVE_1, OUTPUT);
  pinMode(ESCA, OUTPUT);
  pinMode(ESCB, OUTPUT);
  
  pinMode(SENSOR, INPUT);
  pinMode(COMP_SWITCH, INPUT);
  pinMode(VALVE1_SWITCH, INPUT);

  //Motor Control Pins
  MB.attach(8); //ESCB

  //Set relay pins to high (relay is ACTIVE LOW)
  digitalWrite(COMPRESSOR, HIGH);
  digitalWrite(VALVE_1, HIGH);
  digitalWrite(ESCA, HIGH);
  digitalWrite(ESCB, HIGH);

  arm(MA);
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
  Serial.print(", CSwitch: "); 
  Serial.print(digitalRead(COMP_SWITCH)); 
  Serial.print(", VSwitch: "); 
  Serial.println(digitalRead(VALVE1_SWITCH));

  
  pressure = SYSTEM_PRESSURE + 1; //Comment out for Automatic Compressor operation
///////////////////////////////////////////////////////////////////////////////////////////////  
  digitalWrite(ESCA, LOW); //Power ESCs
  digitalWrite(ESCB, LOW);
  setSpeed(MA,0); //Set speed to 0
  setSpeed(MB,0);

//Control  
  if((digitalRead(COMP_SWITCH) == HIGH) && (digitalRead(VALVE1_SWITCH) == HIGH)){ //Run Motor program if push both buttons at the same time
    delay(1000);
    
    //setupESC(MB);
    runESCTest(MB);
    
    delay(1000);
  }
  else{

    if(pressure > SYSTEM_PRESSURE){   //First check if system pressure is too high, turn off compressor
      digitalWrite(COMPRESSOR, HIGH);
    }
 
    if((pressure < SYSTEM_PRESSURE) || (digitalRead(COMP_SWITCH) == HIGH)){   //If pressure is too low, or overriden by manual switch, turn on compressor
      digitalWrite(COMPRESSOR, LOW);
    }
    else{
      digitalWrite(COMPRESSOR, HIGH);
    }

    if(digitalRead(VALVE1_SWITCH) == HIGH){   //If valve switch is flipped open valve
      digitalWrite(VALVE_1, LOW);
    }
    else{
      digitalWrite(VALVE_1, HIGH);
    }
  }
  
  delay(100);
} //End of main program
///////////////////////////////////////////////////////////////////////////////////////////////

//write(-100) = Full backwards
//write(100) = Full forwards
void runESCTest(Servo M){ //Run Motor test code
  int speed; //Speed variable

  setSpeed(M, 20);
  delay(1500);

  setSpeed(M, 0);
  delay(2000);
  
  setSpeed(M, -20);
  delay(1500);
  
  setSpeed(M, 0);
  delay(1000); //Turns off for 1 second

 } //End of ESC Test program
 ///////////////////////////////////////////////////////////////////////////////////////////////
 
void setupESC(Servo M){ //Run setup code to normalize ESC input ranges
  int speed; //Speed variable

  setSpeed(M, 100);  //High forward
  delay(6000);

  setSpeed(M, -100); //High reverse
  delay(10000);

 } //End of ESC Setup
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
