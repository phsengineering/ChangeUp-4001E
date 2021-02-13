#include "main.h"
#include "subsystems.hpp"
#include <stdio.h>
#include <math.h>

using namespace pros;
/*
pros::ADIEncoder rightEncoder ('G', 'H', false);
pros::ADIEncoder middleEncoder ('A', 'B', false);
pros::ADIEncoder leftEncoder ('D', 'C', true);

double LEFTENCODER, RIGHTENCODER, MIDDLEENCODER;

double PI = 3.14159265;

double diameterOfTrack = 2.75; //inches
double circumference = 2*PI*(diameterOfTrack/2);

double sl = 13.875 / 2;
double sr = 13.875 / 2;
double ss = 5.75;

double theta, rr, dly, dlx;

void odom2() {
  LEFTENCODER = leftEncoder.get_value();
  RIGHTENCODER = rightEncoder.get_value();
  MIDDLEENCODER = middleEncoder.get_value();

//  printf("[l: %f r: %f m: %f]\n", LEFTENCODER, RIGHTENCODER, MIDDLEENCODER);

  double leftCorrection = (LEFTENCODER / 360) * circumference;
  double rightCorrection = (RIGHTENCODER / 360) * circumference;
  double middleCorrection = (MIDDLEENCODER / 360) * circumference;

  theta = ((leftCorrection - rightCorrection) / (sl + sr));

  rr = (rightCorrection / (theta / 180/PI)) + sr;

  dlx = 2 * (sin(theta/2) * ((middleCorrection / theta) + ss));

  dly = 2 * (sin(theta/2) * ((rightCorrection / theta) + sr));

  printf("[Theta: %f X: %f Y: %f]\n", (theta*(180/PI)), dlx, dly);
}
*/
void odom2() {
  
}
