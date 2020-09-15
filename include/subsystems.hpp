      #pragma once
#include "main.h"

using namespace pros;

void goDistancePID(double inches, double speed);
void turnAnglePID(double degreeInput);
void drive(int y, int r);
void turnDrive(double y);
void autonDrive(double y, double max);
void driveVelLeft(double speed);
void driveVelRight(double speed);
void curveTurn(double degreeInput);
void init();



extern Motor driveRF;
extern Motor driveRB;
extern Motor driveLF;
extern Motor driveLB;
