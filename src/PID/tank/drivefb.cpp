#include "main.h"
#include "subsystems.hpp"
#include <stdio.h>

using namespace pros;

void driveStraight(double input, double thatDelay) {

  double direction;

  if (input < 0) {
    direction = -1;
  } else {
    direction = 1;
  }

  double timer;

  tareAll();
  leftEncoder.reset();
  rightEncoder.reset();
  middleEncoder.reset();

  double distance = ((input / 8.9) * 360);

  //double average = (fabs(driveRF.get_position()) + fabs(driveRB.get_position()) + fabs(driveLF.get_position()) + fabs(driveLB.get_position())) / 4;
  double average = leftEncoder.get_value() + rightEncoder.get_value() / 2;

  double TARGET = average + distance;
  double currentValue = average;

  double currentError = TARGET - currentValue;
  double previousError = 0;

  double kP  =  0.2;
  double kI  =  0.0;
  double kD  =  0.0;

	double acceptableError = 0.0;
  double maxNumberOfCorrections = 999999999;

  double maxSpeed = 500;

  double speedCorrection = 4;

  bool driveMotors = true;
  bool displayValues = true;

  double correctionAmount = 0;

  while(fabs(currentError) > acceptableError || fabs(previousError) > acceptableError) {

    double p  = kP * currentError;
    double i  = kI;
    double d  = kD * (currentError - previousError);

    double command = (p + i + d);

    double oppset = 0;

    if (fabs(command) > maxSpeed) {
      if (command < 0) {
        fbauton(-maxSpeed);
      } else {
        fbauton(maxSpeed);
      }
    } else {
      fbauton(command, 0);
    }

    average = (leftEncoder.get_value() + rightEncoder.get_value()) / 2;

    currentValue = average;
    previousError = currentError;
    currentError = TARGET - currentValue;

     if (displayValues == true) {
       printf("currentError: %lf", currentError);
       printf("   command: %lf", command);
       printf("   position: %lf", average);
       printf("   target: %lf\n", TARGET);
     }

    timer++;
    delay(10);
  //  odom2();
  }

  correctionAmount = 0;
  stopAllDrive();
  timer = 0;

  delay(thatDelay);
}
