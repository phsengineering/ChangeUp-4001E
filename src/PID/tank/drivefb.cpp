#include "main.h"
#include "subsystems.hpp"
#include <stdio.h>

using namespace pros;

void driveStraight(double input) {

  double timer;

  tareAll();
  leftEncoder.reset();
  rightEncoder.reset();
  middleEncoder.reset();

  double distance = ((input / 8.9) * 360);

  //double average = (fabs(driveRF.get_position()) + fabs(driveRB.get_position()) + fabs(driveLF.get_position()) + fabs(driveLB.get_position())) / 4;
  double average = fabs(leftEncoder.get_value() + rightEncoder.get_value()) / 2;

  double TARGET = average + distance;
  double currentValue = average;

  double currentError = TARGET - currentValue;
  double previousError = 0;

  double kP  =  0.005;
  double kI  =  0.0;
  double kD  =  0.12;

	double acceptableError = 0.1;
  double maxNumberOfCorrections = 100;

  double speedCorrection = 5;

  bool driveMotors = true;
  bool displayValues = true;

  double correctionAmount = 0;

  while(fabs(currentError) > acceptableError || fabs(previousError) > acceptableError) {

    double p  = kP * currentError;
    double i  = kI;
    double d  = kD * (currentError - previousError);

    double command = (p + i + d) * speedCorrection;

    double oppset = 0;

    if (driveMotors == true && correctionAmount < maxNumberOfCorrections) {
		    if (fabs(command) < 1) {
						if (command > 0) {
							normalDrive(25, oppset);
						} else {
							normalDrive(-25, oppset);
						}
            correctionAmount++;
				} else {
              if (command*18 < 50) {
				        normalDrive(command * 19, oppset);
              } else {
                normalDrive(60, oppset);
              }
				   }
			} else {
        break;
      }

    average = fabs(leftEncoder.get_value() + rightEncoder.get_value()) / 2;

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
  }

  correctionAmount = 0;
  stopAllDrive();
  timer = 0;
}
