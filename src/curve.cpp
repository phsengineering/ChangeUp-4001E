#include "main.h"
#include "subsystems.hpp"
#include <stdio.h>

using namespace pros;

void curve() {
  double speed = 10000;

  double leftDistance = 1;
  double rightDistance = 0.5;

  driveLF.tare_position();
  driveRF.tare_position();
  driveLB.tare_position();
  driveRB.tare_position();

  double lefts, rights = 0;

  double LEFTTARGET = leftDistance;
  double RIGHTTARGET = rightDistance;

  double leftCurrentValue = 0;
  double leftCurrentError = LEFTTARGET - leftCurrentValue;
  double leftPreviousError = 0;

  double rightCurrentValue = 0;
  double rightCurrentError = RIGHTTARGET - rightCurrentValue;
  double rightPreviousError = 0;

  double lkP = 2.5;
  double lkI = 0.0;
  double lkD = 12.0;

  double rkP = 2.5;
  double rkI = 0.0;
  double rkD = 12.0;

  double acceptableError = 0.04;
  double speedCorrection = 1;

  double leftCorrection = 1.0; // increase if veering to left
  double rightCorrection = 1.0; // increase if veering to right

  double timer = 0;

  while (fabs(leftCurrentError > acceptableError) || fabs(rightCurrentError) > acceptableError) {
    double lp = lkP * leftCurrentError;
    double li = lkI;
    double ld = lkD * (leftCurrentError - leftPreviousError);
    double leftCommand = lp + li + ld;

    double rp = rkP * rightCurrentError;
    double ri = rkI;
    double rd = rkD * (rightCurrentError - rightPreviousError);
    double rightCommand = rp + ri + rd;

    if (fabs(leftCommand) < 1) {
      if (leftCommand > 0) {
        leftDrive(18, speed);
      } else {
        leftDrive(-18, speed);
      }
    } else{
      leftDrive(leftCommand * 15 * leftCorrection, speed);
    }

    if (fabs(rightCommand) < 1) {
      if (rightCommand > 0) {
        rightDrive(18, speed);
      } else {
        rightDrive(-18, speed);
      }
    } else{
      rightDrive(rightCommand * 15 * rightCorrection, speed);
    }

    leftCurrentValue = (driveLF.get_position() + driveLB.get_position()) / 2;
		rightCurrentValue = (driveRF.get_position() + driveRB.get_position()) / 2;

    leftPreviousError = leftCurrentError;
    leftCurrentError = LEFTTARGET - leftCurrentValue;

    rightPreviousError = rightCurrentError;
    rightCurrentError = RIGHTTARGET - rightCurrentValue;

    double sideDifference = leftCurrentValue - rightCurrentValue;

  	printf("%lf", timer);
	  printf(",%lf", sideDifference);
  	printf(",%lf", leftCurrentValue);
  	printf(",%lf\n", rightCurrentValue);
  	delay(10);

    timer++;

  }
  stopAllDrive();
  timer = 0;
}
