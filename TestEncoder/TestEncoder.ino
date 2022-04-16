#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>

#define EncoderPinA 2   // Encoder Pin A pin 2 and pin 3 are inturrpt pins
#define EncoderPinB 5   // Encoder Pin B

//Initialize Variables
long counts = 0; //counts the encoder counts. The encoder has ~233counts/rev

void setup() {
  Serial.begin(115200);
  
  pinMode(EncoderPinA, INPUT); //initialize Encoder Pins
  pinMode(EncoderPinB, INPUT); 
   
  digitalWrite(EncoderPinA, LOW); //initialize Pin States
  digitalWrite(EncoderPinB, LOW);
  
  attachInterrupt(0, readEncoder, CHANGE); //attach interrupt to PIN 2 
}

void loop() {
  Serial.println(counts);
}

void readEncoder() //this function is triggered by the encoder CHANGE, and increments the encoder counter
{ 
  if(digitalRead(EncoderPinB) == digitalRead(EncoderPinA))
  {
    counts = counts-1; //you may need to redefine positive and negative directions
  }
  else
  {
    counts = counts+1;
  }
}
