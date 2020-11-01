#include "main.h"
#include "subsystems.hpp"
#include <stdio.h>
#include <math.h>

using namespace pros;

pros::ADIEncoder leftEncoder ('E', 'F', false);
pros::ADIEncoder rightEncoder ('C', 'D', false);
pros::ADIEncoder middleEncoder ('A', 'B', true);

double PI = 3.141592;

double diameterOfTrack = 2.75; //inches
double distanceBetweenLeftRight = 13.875; //inches
double distanceFromBackToTrack = 5.75; //inches

double circumference = 2*PI*(diameterOfTrack/2);

double LEFTENCODER, RIGHTENCODER, MIDDLEENCODER;

double alpha, h, rl, rr, x, y;
double alpha2, h2, rl2, rr2, x2, y2;

double combx, comby;


void odom(bool reset) {

  if (reset == true) {
    leftEncoder.reset();
    rightEncoder.reset();
    middleEncoder.reset();
    reset = false;
  }

  LEFTENCODER = leftEncoder.get_value();
  RIGHTENCODER = rightEncoder.get_value();
  MIDDLEENCODER = middleEncoder.get_value();

  double leftCorrection = (LEFTENCODER / 360) * circumference;
  double rightCorrection = (RIGHTENCODER / 360) * circumference;
  double middleCorrection = (MIDDLEENCODER / 360) * circumference;

  alpha = ((rightCorrection - leftCorrection) / distanceBetweenLeftRight) * 57.2958;

  rl = leftCorrection / (alpha/57.2958);
  rr = rl + distanceBetweenLeftRight;
  h = 2 * ((rl + (rr - rl)) * sin(alpha/57.2958/2)); // (rr - rl) might have to change to w/2
  x = sin(fabs(alpha/57.2958/2)) * h;
  y = cos(fabs(alpha/57.2958/2)) * h;

  rl2 = leftCorrection / (alpha/57.2958);
  rr2 = rl2 + distanceBetweenLeftRight;
  h2 = 2 * ((middleCorrection + distanceFromBackToTrack) * sin(alpha/57.2958/2));
  y2 = sin(fabs(alpha/57.2958/2)) * h2;
  x2 = cos(fabs(alpha/57.2958/2)) * h2;

  combx = x + x2;
  comby = y + y2;

  printf(" \033[1;37m Encoder values: \033[1;32m Left: %f \033[1;33m Right: %f \033[1;34m Middle: %f \033[1;35m ALPHA: %f \033[1;36m H: %f \033[1;37m X: %f \033[1;38m Y: %f\n", leftCorrection, rightCorrection, middleCorrection, alpha, h, combx, comby);
}

void driveFor(int seconds) {
  int y = 100;
  int x, rot = 0;

  y *= 11000.0 / 127.0;
  x *= 11000.0 / 127.0;
  rot *= 11000.0 / 127.0;

  int LF  =  y + x + rot;
  int LB  =  y - x + rot;
  int RF  = -y + x + rot;
  int RB  = -y - x + rot;

  driveLF.move_voltage(LF);
  driveLB.move_voltage(LB);
  driveRF.move_voltage(RF);
  driveRB.move_voltage(RB);

  delay(seconds);

  stopAllDrive();
}
