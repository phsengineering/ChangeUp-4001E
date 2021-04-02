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

  double distance = (((input / 8) * 360) + 1) / 1.1;

  double imu1 = thatIMU.get_rotation();
  double imu2 = thatIMU2.get_rotation();
  double angleTest = ((imu1 + imu2) / 2);

  //double average = (fabs(driveRF.get_position()) + fabs(driveRB.get_position()) + fabs(driveLF.get_position()) + fabs(driveLB.get_position())) / 4;
  double average = leftEncoder.get_value() + rightEncoder.get_value() / 2;

  double TARGET = average + distance;
  double currentValue = average;

  double currentError = TARGET - currentValue;
  double previousError = 0;

  double kP  =  0.15;
  double kI  =  0;
  double kD  =  1.5;

	double acceptableError = 0.0;
  double maxNumberOfCorrections = 30;

  double maxSpeed;

  if (input < 0) {
    maxSpeed = 127;
  } else {
    maxSpeed = 127;
  }

  double minSpeed = 30;

  double speedCorrection = 1;

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
        fbautonBACK(-maxSpeed);
      } else {
        fbauton(maxSpeed);
      }
    } else if (fabs(command) < minSpeed) {
      if (correctionAmount < maxNumberOfCorrections) {
        if (command < 0) {
          minSpeed = 20;
          fbautonBACK(-minSpeed);
          correctionAmount++;
        } else {
          fbauton(minSpeed);
        }
      } else {
        break;
      }
    } else {
      if (command < 0) {
        fbauton(command);
      } else {
        fbauton(command);
      }
    }

    average = (leftEncoder.get_value() + rightEncoder.get_value()) / 2;

    currentValue = average;
    previousError = currentError;
    currentError = TARGET - currentValue;

     if (displayValues == true) {
       /*printf("currentError: %lf", currentError);
       printf("   command: %lf", command);
       printf("   position: %lf", average);
       printf("   target: %lf\n", TARGET); */
    //   printf("   target: %lf\n", middleEncoder.get_value());
     }

    timer++;
    delay(10);
  //  odom2();
  }
  imu1 = thatIMU.get_rotation();
  imu2 = thatIMU2.get_rotation();
  double angleEnd = ((imu1 + imu2) / 2) - angleTest;
  printf("ANGLE BAD: %lf\n", (angleEnd));

  correctionAmount = 0;
  stopAllDrive();
  timer = 0;

  delay(thatDelay);
}
