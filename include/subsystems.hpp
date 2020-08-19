#pragma once
#include "main.h"

using namespace pros;

void goDistancePID(double inches);
void turnAnglePID(double angle);
void drive(int y, int r);
void turnDrive(int y);



extern Motor driveRF;
extern Motor driveRB;
extern Motor driveLF;
extern Motor driveLB;
