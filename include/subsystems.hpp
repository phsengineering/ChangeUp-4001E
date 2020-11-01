#pragma once
#include "main.h"

using namespace pros;

void goDistancePID(double inches, double speed);
void turnAnglePID(double degreeInput);
void drive(int y, int r);
void turnDrive(double y);
void autonDrive(double y, double max);
void autonDriveVary(double lefts, double rights, double max);
void driveVelLeft(double speed);
void driveVelRight(double speed);
void curveTurn(double degreeInput);
void init();
void curve();
void rightDrive(double y, double max);
void leftDrive(double y, double max);
void odom(bool reset);
void showcasePID(double inches, double speed);
void stopAllDrive();
void dualDrive(double inches, double speed);
void imuTurn(double angle);
void xDriveStrafe(int y, int x, int rot);
void xDriveFB(double distance);
void xDriveLR(double distance);
void tareAll();
void xDriveTurn(double degreeInput);
void driveFor(int seconds);
void odom2();
void trackTurn(double degreeInput);

extern Motor driveRF;
extern Motor driveRB;
extern Motor driveLF;
extern Motor driveLB;

extern Imu imu_sensor;
