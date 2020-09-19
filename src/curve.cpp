#include "main.h"
#include "subsystems.hpp"
#include <stdio.h>

using namespace pros;


double leftDistance = 8.75;
double rightDistance = 1;

double leftTarget, rightTarget;
double leftHalfway, rightHalfway;

double lkP = 2.5;
double lkI = 0;
double lkD = 12.0;

double rkP = 2.5;
double rkI = 0;
double rkD = 12.0;

double maxRate = 35;

double speed = 5000;
double speedCorrection = 20;

bool driveMotors = true;

double leftCommand, rightCommand;

void curve() {
  driveLF.tare_position();
  driveRF.tare_position();
  driveLB.tare_position();
  driveRB.tare_position();

  leftTarget = driveLB.get_position() + leftDistance;
  leftHalfway = driveLB.get_position() + leftDistance / 4;

  rightTarget = driveLB.get_position() + rightDistance;
  rightHalfway = driveLB.get_position() + rightDistance / 4;

  double leftCurrent = driveLB.get_position();
  double rightCurrent = driveRB.get_position();

  double leftCurrentError = leftTarget - leftCurrent;
  double rightCurrentError = rightTarget - rightCurrent;

  double leftPreviousError = 0;
  double rightPreviousError = 0;

  bool accel = false;

  double acceptableError = 0.025;

  while(fabs(leftCurrentError) > acceptableError || fabs(leftPreviousError) > acceptableError || fabs(rightCurrentError) > acceptableError || fabs(rightPreviousError) > acceptableError) {
    if (fabs(leftCurrentError) > acceptableError || fabs(leftPreviousError) > acceptableError) {
      if(leftDistance > 0 && leftCurrent > leftHalfway)
          accel = false;
      else if(leftDistance < 0 && leftCurrent < leftHalfway)
          accel = false;

      double lp  = lkP * leftCurrentError;
      double li  = lkI;
      double ld  = lkD * (leftCurrentError - leftPreviousError);

      leftCommand = lp + li + ld;

      if(fabs(leftCommand) > maxRate) {
          if(leftCommand > 0)
              leftCommand = maxRate;
          else
              leftCommand = -maxRate;
      }
      if (driveMotors == true) {
        if (fabs(leftCommand) < 1) {
          if (leftCommand > 0) {
            leftDrive(40, speed);
          } else {
            leftDrive(-40, speed);
          }
        } else{
          leftDrive(leftCommand*15*speedCorrection, speed);
        }
      }

      if(accel) {
          if(maxRate < 120)
          maxRate += 10;
      }

      leftCurrent = driveLB.get_position();
      leftPreviousError = leftCurrentError;
      leftCurrentError = leftTarget - leftCurrent;

    } else {
      driveLF.move_velocity(0);
      driveLB.move_velocity(0);
    }
    if (fabs(rightCurrentError) > acceptableError || fabs(rightPreviousError) > acceptableError) {
      if(rightDistance > 0 && rightCurrent > rightHalfway)
          accel = false;
      else if(rightDistance < 0 && rightCurrent < rightHalfway)
          accel = false;

      double rp  = rkP * rightCurrentError;
      double ri  = rkI;
      double rd  = rkD * (rightCurrentError - rightPreviousError);

      rightCommand = rp + ri + rd;

      if(fabs(rightCommand) > maxRate) {
          if(rightCommand > 0)
              rightCommand = maxRate;
          else
              rightCommand = -maxRate;
      }
      if (driveMotors == true) {
        if (fabs(rightCommand) < 1) {
          if (rightCommand > 0) {
            rightDrive(40, speed);
          } else {
            rightDrive(-40, speed);
          }
        } else{
          rightDrive(rightCommand*15*speedCorrection, speed);
        }
      }

      if(accel) {
          if(maxRate < 120)
          maxRate += 10;
      }

      rightCurrent = driveLB.get_position();
      rightPreviousError = rightCurrentError;
      rightCurrentError = rightTarget - rightCurrent;

    } else {
      driveRF.move_velocity(0);
      driveRB.move_velocity(0);
    }
    printf("left current error: %lf", leftCurrentError);
    printf("   left command: %lf", leftCommand);
    printf("   right current error: %lf", rightCurrentError);
    printf("   right Command: %lf \n", rightCommand);
    delay(10);
  }


}
