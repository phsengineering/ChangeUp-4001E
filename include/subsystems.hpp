#pragma once
#include "main.h"

using namespace pros;

void drive(int y, int r);
void init();
void odom(bool reset);
void odom2();
void stopAllDrive();
void tareAll();
void driveFor(double seconds, double power);
void normalDrive(int y, int x);
void autonTurn(double y);
void intakeHandler(double power);
void midRollers(double power);
void topRoller(double power);
void autonHandler();
void driveStraight(double distance, double thatDelay);
void turnAngle(double degreeInput, double thatDelay);
void fbauton(double y);
void score();
void flipout();
void rollerHandler(double power);

extern Motor driveRF;
extern Motor driveRB;
extern Motor driveLF;
extern Motor driveLB;

extern Motor intakeL;
extern Motor intakeR;

extern Motor rollerT;
extern Motor rollerB;

extern Imu thatIMU;
extern Imu thatIMU2;

extern ADIEncoder leftEncoder;
extern ADIEncoder rightEncoder;
extern ADIEncoder middleEncoder;
