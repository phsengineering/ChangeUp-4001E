#include "main.h"
#include "subsystems.hpp"
#include <stdio.h>

using namespace pros;

void xDriveFB(double distance) {

  double timer;

  tareAll();

  double average = (fabs(driveRF.get_position()) + fabs(driveRB.get_position()) + fabs(driveLF.get_position()) + fabs(driveLB.get_position())) / 4;

  double TARGET = average + distance;
  double currentValue = average;

  double currentError = TARGET - currentValue;
  double previousError = 0;

  double kP  =  2.3;
  double kI  =  0;
  double kD  =  12.0;

	double acceptableError = 0.02;
  double speedCorrection = 1;

  bool driveMotors = true;
  bool displayValues = true;

  while(fabs(currentError) > acceptableError || fabs(previousError) > acceptableError) {

    double p  = kP * currentError;
    double i  = kI;
    double d  = kD * (currentError - previousError);

    double command = p + i + d;

    if (driveMotors == true) {
		    if (fabs(command) < 1) {
						if (command > 0) {
							xDriveStrafe(25, 0, 0);
						} else {
							xDriveStrafe(-25, 0, 0);
						}
				} else {
              if (command*18 < 50) {
				        xDriveStrafe(command * 18, 0, 0);
              } else {
                xDriveStrafe(50, 0, 0);
              }
				   }
			}

    average = fabs(driveRF.get_position()) + fabs(driveRB.get_position()) + fabs(driveLF.get_position()) + fabs(driveLB.get_position());

    currentValue = average;
    previousError = currentError;
    currentError = TARGET - currentValue;

    printf("%lf", timer);
    printf(",%lf", driveRF.get_position());
    printf(",%lf", driveRB.get_position());
    printf(",%lf", driveLF.get_position());
    printf(",%lf\n", driveLB.get_position());
    timer++;
    delay(10);
  }
  stopAllDrive();
  timer = 0;
}
