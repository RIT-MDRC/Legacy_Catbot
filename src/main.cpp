#include <Arduino.h>

#include <Potentiometer.h>

Potentiometer pot(A0, 320, 1024);

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop()
{
  // put your main code here, to run repeatedly:
  Serial.println(pot.getReading());
  delay(100);
}