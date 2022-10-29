#include <Arduino.h>

#include <Potentiometer.h>

Potentiometer pot(A0, 320, 1023);

void setup()  // Runs once at the start
{
  __hook(&Potentiometer::RotationChangeEvent, pot, onRotationChanged);
  Serial.begin(9600);
}

void loop()   // Runs repeatedly
{
  // Have potentiometer always listen for changes in rotation
  pot.listenForRotation();
  delay(100);
}

// This is a test to demonstrate the rotation listener, can be removed later
void onRotationChanged(int rotation)
{
  Serial.println(rotation);
}