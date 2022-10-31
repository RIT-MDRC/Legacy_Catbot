#include <Servo.h>



int value = 900; //low threshold
int temp; //used to filter null characters


Servo firstESC; 


void setup() {

 
 firstESC.attach(13);   //pin 13

 Serial.begin(9600);   // start serial at 9600 baud


}


void loop() {


/*
1) Run Arduino Code
2) Turn on ESC power supply
3) Wait for beeps, enter high threshold, wait again, enter low threshold
*/

 if(Serial.available()>0){ 

   temp = Serial.parseInt();   // parse an integer from serial
 }
 
 if((temp>=900) && (temp<=2000)) //checking for invalid characters
 {
  value = temp;
 }
 
   Serial.println(value);   //user feedback
   firstESC.writeMicroseconds(value);

 delay(100);
}
