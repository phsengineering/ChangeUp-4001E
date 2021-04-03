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
void turnTest(double degreeInput, double thatDelay);
void fbauton(double y, double slew);
void fbautonBACK(double y);
void score();
void flipout();
void rollerHandler(double power);
void score2();
void okapiDrive();
void okapiPath();
void skills();
void auton2balls(bool left);
void auton3balls(bool left);
void splitFB(double L, double R);

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

extern Controller mainController;

extern std::string autons[11];
extern int current;
extern double delayBetween;
