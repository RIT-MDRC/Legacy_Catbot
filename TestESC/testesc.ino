 #include <Servo.h>



int value = 2000; //tialize the variables you need


Servo firstESC; // you can control 2 or more servos simultaneously


void setup() {

 
 firstESC.attach(13);   

 Serial.begin(9600);   // start serial at 9600 baud


}


void loop() {


//First connect your ESC WITHOUT arming. Then open the serial and follow the instructions.

 if(Serial.available()>0){ 

   value = Serial.parseInt();   // parse an integer from serial
 }
 

 Serial.println(value);
 firstESC.writeMicroseconds(value);
}