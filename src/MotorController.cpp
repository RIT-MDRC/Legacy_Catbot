#include "MotorController.h"

MotorController::MotorController(Motor *_motor, Potentiometer *_pot, int _minDegrees, int _maxDegrees)
{
  motor = _motor;
  pot = _pot;
  minDegrees = _minDegrees;
  maxDegrees = _maxDegrees;
}

// // Calibrate the potentiometer
// void MotorController::calibrate();

// // Stop Motor
// void MotorController::stop();

// // Turn motor by the amount of degrees with a given speed
// void MotorController::turn(int degree, int speedPercent);

// // Turn motor by the amount of degrees with default speed
// void MotorController::turn(int degree);

// // Turn the motor to a specific degree with a default speed
// void MotorController::turnTo(int degree);

// // Turn the motor to a specific degree with a given speed
// void MotorController::turnTo(int degree, int speedPercent);

// // Turn the motor to a specific degree with in a given time
// void MotorController::turnToWithIn(int degree, int time);

// int MotorController::getCurrentDegree();

// int MotorController::getMinDegrees();

// int MotorController::getMaxDegrees();

// int MotorController::getDistanceToMax();

// int MotorController::getDistanceToMin();

// int MotorController::getDegreesToClosest();

// int MotorController::getDirectionToClosest();

// int MotorController::getDirectionToFarthest();

// int MotorController::getDirectionToMax();

// int MotorController::getDirectionToMin();
