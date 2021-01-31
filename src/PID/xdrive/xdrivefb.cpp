#include "main.h"
#include "subsystems.hpp"
#include <stdio.h>

using namespace pros;

void asdf(double distance) {

  double timer;

  tareAll();

  double average = (fabs(driveRF.get_position()) + fabs(driveRB.get_position()) + fabs(driveLF.get_position()) + fabs(driveLB.get_position())) / 4;

  printf("   target: %lf\n", average);

  double TARGET = average + distance;
  double currentValue = average;

  double currentError = TARGET - currentValue;
  double previousError = 0;

  double kP  =  2.5; //2.3
  double kI  =  0;
  double kD  =  12.0;

	double acceptableError = 0.04;
  double speedCorrection = 1;

  bool driveMotors = true;
  bool displayValues = true;

  while(fabs(currentError) > acceptableError || fabs(previousError) > acceptableError) {

    double p  = kP * currentError;
    double i  = kI;
    double d  = kD * (currentError - previousError);

    double command = p + i + d;

    double oppset = -5;

    if (driveMotors == true) {
		    if (fabs(command) < 1) {
						if (command > 0) {
							normalDrive(25, oppset);
						} else {
							normalDrive(-25, oppset);
						}
				} else {
              if (command*18 < 50) {
				        normalDrive(command * 30, oppset);
              } else {
                normalDrive(50, oppset);
              }
				   }
			}

    average = fabs(driveRF.get_position()) + fabs(driveRB.get_position()) + fabs(driveLF.get_position()) + fabs(driveLB.get_position());

    currentValue = average;
    previousError = currentError;
    currentError = TARGET - currentValue;

     if (displayValues == true) {
       printf("currentError: %lf", currentError);
       printf("   command: %lf", command);
       printf("   position: %lf", currentValue);
       printf("   target: %lf\n", TARGET);
     }

    timer++;
    delay(10);
  }
  stopAllDrive();
  timer = 0;
}
