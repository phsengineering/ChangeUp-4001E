#include "main.h"
#include "subsystems.hpp"
#include <stdio.h>

using namespace pros;

void dual(double input, double thatDelay) {

  double speed = 5500;

  leftEncoder.reset();
  rightEncoder.reset();

  double leftCurrentValue = leftEncoder.get_value();
  double rightCurrentValue = rightEncoder.get_value();

  double lefts, rights = 0;

  double distance = input;

  double TARGET = distance;
  double HALFWAY = distance / 4;

  double leftCurrentError = TARGET - leftCurrentValue;
  double leftPreviousError = 0;

  double rightCurrentError = TARGET - rightCurrentValue;
  double rightPreviousError = 0;

  double lkP = 0.02;
  double lkI = 0;
  double lkD = 0.01;

  double rkP = 0.02;
  double rkI = 0;
  double rkD = 0.01;

  double acceptableError = 0;
  double speedCorrection = 1;

  double leftCorrection = 1.0; // increase if veering to left
  double rightCorrection = 1.0; // increase if veering to right

  double timer = 0;

  while (fabs(leftCurrentError) > acceptableError || fabs(leftPreviousError) > acceptableError) {
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
        leftDrive(25, speed);
      } else {
        leftDrive(-25, speed);
      }
    } else{
      leftDrive(leftCommand * 15 * leftCorrection, speed);
    }

    if (fabs(rightCommand) < 1) {
      if (rightCommand > 0) {
        rightDrive(25, speed);
      } else {
        rightDrive(-25, speed);
      }
    } else{
      rightDrive(rightCommand * 15 * rightCorrection, speed);
    }

    leftCurrentValue = leftEncoder.get_value();
    rightCurrentValue = rightEncoder.get_value();

    leftPreviousError = leftCurrentError;
    leftCurrentError = TARGET - leftCurrentValue;

    rightPreviousError = rightCurrentError;
    rightCurrentError = TARGET - rightCurrentValue;

    double sideDifference = leftCurrentValue - rightCurrentValue;

  	printf("%lf", timer);
    printf(",%lf", leftCurrentError);
    printf(",%lf", leftCommand);
	  printf(",%lf", sideDifference);
  	printf(",%lf", leftCurrentValue);
  	printf(",%lf\n", rightCurrentValue);
  	delay(10);

    timer++;

  }
  stopAllDrive();
  timer = 0;
  delay(thatDelay);
}
