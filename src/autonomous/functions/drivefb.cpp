#include "main.h"
#include "subsystems.hpp"
#include <stdio.h>

using namespace pros;

void driveStraight(double input, double thatDelay) {
  leftEncoder.reset();
  rightEncoder.reset();
  middleEncoder.reset();

  double distance = (((input / 8) * 360) + 1) / 1.1;

  double average = 0;
  double TARGET = distance;
  double currentValue;

  double currentError = TARGET;
  double previousError = 0;

  double kP  =  0.11;
  double kI  =  0;
  double kD  =  1.5;

  double acceptableError = 0.0;
  double maxNumberOfCorrections = 30;

  double maxSpeed = 127;
  double minSpeed = 25;

  bool driveMotors = false;
  bool displayValues = true;

  double correctionAmount = 0;

  ///// slew correction //////

  double skP = 0;
  double skI = 0;
  double skD = 0;

  double slewTarget = 0;
  double slewCurrentValue = 0;
  double slewPreviousError = 0;
  double slewCurrentError = 0;
  double slewAcceptableError = 5;

  while(fabs(currentError) > acceptableError) {

    double p  = kP * currentError;
    double i  = kI;
    double d  = kD * (currentError - previousError);
    double command = (p + i + d);

    double sp = skP * slewCurrentError;
    double si = skI;
    double sd = skD * (slewCurrentError - slewPreviousError);
    double slewCommand = (sp + si + sd);

    if (fabs(command) > maxSpeed) {
      if (command < 0) {
        fbauton(-maxSpeed, slewCommand);
      } else {
        fbauton(maxSpeed, slewCommand);
      }
    } else if (fabs(command) < minSpeed) {
      if (correctionAmount < maxNumberOfCorrections) {
        if (command < 0) {
          minSpeed = 20;
          fbauton(-minSpeed, slewCommand);
          correctionAmount++;
        } else {
          fbauton(minSpeed, slewCommand);
        }
      } else {
          break;
      }
    } else {
      if (command < 0) {
        fbauton(command, slewCommand);
      } else {
        fbauton(command, slewCommand);
      }
    }

    average = (leftEncoder.get_value() + rightEncoder.get_value()) / 2;
    currentValue = average;
    previousError = currentError;
    currentError = TARGET - currentValue;

    slewCurrentValue = middleEncoder.get_value();
  //  slewCurrentValue = leftEncoder.get_value() - rightEncoder.get_value();
    slewPreviousError = slewCurrentError;
    slewCurrentError = slewTarget - slewCurrentValue;

     if (displayValues == true) {
    /*   printf("currentError: %lf", currentError);
       printf("   command: %lf", command);
       printf("   position: %lf", average);
       printf("   target: %lf\n", TARGET); */

       printf("slew error: %lf", slewCurrentError);
       printf("   command: %lf", slewCommand);
       printf("   position: %lf \n", slewCurrentValue);
      // printf("   target: %lf\n", middleEncoder.get_value());
     }
    delay(2);
  }
  correctionAmount = 0;
  stopAllDrive();

  delay(thatDelay);
}
