#include "Motor.h"

#define DELAY 100 // ms of delay between writing to ESCs

Motor::Motor(int _motorPin, int _mapLow, int _mapHigh, int _mapMiddle)
{
  motorPin = _motorPin;
  mapLow = _mapLow;
  mapHigh = _mapHigh;
  mapMiddle = _mapMiddle;

  esc.attach(_motorPin);
  arm();
}

void Motor::arm()
{
  // Stops the motor (calls mapMiddle because negative direction is also in the positive value)
  esc.writeMicroseconds(mapMiddle);
}

// Runs the motor at a given percentage of speed for the given number of seconds.
// A negative value for seconds will make the motor run infinitely.
void Motor::run(int speedPercent, double seconds)
{
  // Only allow speed percentages in the range [-100%, 100%]
  if (speedPercent > 100 && speedPercent < -100)
  {
    return;
  }

  // If user sets 0% speed, they're essentially just arming the motor
  if (speedPercent == 0)
  {
    arm();
    return;
  }

  // Middle value might not be in the actual center, so map() will have different
  // ranges based on where the "middle" is
  int velocity;

  if (speedPercent > 0)
  {
    velocity = map(speedPercent, 0, 100, mapMiddle, mapHigh);
  }
  else
  {
    velocity = map(speedPercent, -100, 0, mapLow, mapMiddle);
  }

  esc.writeMicroseconds(velocity);
  
  // Run infinitely (or until another run() is called) if a negative value is passed for seconds
  if (seconds >= 0)
  {
    delay(seconds * 1000);
    arm();
  }
}