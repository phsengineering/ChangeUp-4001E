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
void asdf(double distance);
void xDriveLR(double distance);
void tareAll();
void xDriveTurn(double degreeInput);
void driveFor(double seconds, double power);
void odom2();
void trackTurn(double degreeInput);
void normalDrive(int y, int x);
void autonTurn(double y);
void intakeHandler(double power);
void midRollers(double power);
void topRoller(double power);
void autonHandler();
void driveStraight(double distance, double thatDelay);
void turnAngle(double degreeInput, double thatDelay);
void dual(double distance, double thatDelay);
void fbauton(double y, double x);
void score();

extern Motor driveRF;
extern Motor driveRB;
extern Motor driveLF;
extern Motor driveLB;

extern Motor intakeL;
extern Motor intakeR;

extern Motor rollerT;
extern Motor rollerB;

extern Imu thatIMU;

extern ADIEncoder leftEncoder;
extern ADIEncoder rightEncoder;
extern ADIEncoder middleEncoder;
