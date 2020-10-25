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

    if (driveMotors == true) {
		    if (fabs(command) < 1) {
						if (command > 0) {
							xDriveStrafe(25, 0, 0);
						} else {
							xDriveStrafe(-25, 0, 0);
						}
				} else {
              if (command*18 < 50) {
				        xDriveStrafe(command * 20, 0, 0);
              } else {
                xDriveStrafe(40, 0, 0);
              }
				   }
			}

    average = fabs(driveRF.get_position()) + fabs(driveRB.get_position()) + fabs(driveLF.get_position()) + fabs(driveLB.get_position());

    currentValue = average;
    previousError = currentError;
    currentError = TARGET - currentValue;

     pros::c::imu_accel_s_t accel = imu_sensor.get_accel();

    printf("%lf,", timer);
    printf("%lf,", accel.x);
    printf("%lf,", accel.y);
    printf("%lf\n", accel.z);
/*
    printf(",%lf", driveRF.get_position());
    printf(",%lf", driveRB.get_position());
    printf(",%lf", driveLF.get_position());
    printf(",%lf\n", driveLB.get_position());
    */
    timer++;
    delay(10);
  }
  stopAllDrive();
  timer = 0;
}
