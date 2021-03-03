#include "main.h"
#include "subsystems.hpp"
#include <stdio.h>
#include <math.h>

using namespace pros;

double delayBetween = 250;

void autonHandler() {

  flipout();

  delay(200);

  intakeHandler(-12000);
  rollerB.move_voltage(-12000);

  delay(500);

  driveStraight(36, 0); //23.5
  intakeHandler(0);
  rollerB.move_voltage(0);

  delay(750);

  turnAngle(-73, delayBetween);

  driveStraight(18, 100);

  score();

  intakeHandler(2000);
  driveStraight(-30, delayBetween);
/*
  intakeHandler(12000);

  turnAngle(45, delayBetween);

  intakeHandler(-12000);
  driveStraight(25, delayBetween);
  rollerT.move_voltage(0);
  rollerB.move_voltage(0);
  intakeHandler(0);
  driveStraight(-15, delayBetween);
  rollerB.move_voltage(-12000);
  rollerT.move_voltage(-12000);
  delay(700);
  rollerB.move_voltage(0);
  rollerT.move_voltage(0);
  turnAngle(90, delayBetween);

  intakeHandler(-12000);
  driveStraight(32, delayBetween);
  turnAngle(-90, delayBetween);

  driveStraight(19, delayBetween);
  intakeHandler(-12000);
  driveFor(700, 55);
  delay(100);

  rollerT.move_voltage(-12000);
  rollerB.move_voltage(-12000);

  delay(700);
  intakeHandler(0);
  topRoller(0);
  delay(1200);
  topRoller(0);
  midRollers(0);

  delay(1200);

  intakeHandler(0);
  rollerT.move_voltage(0);
  rollerB.move_voltage(0);

  delay(delayBetween);

  driveStraight(-23, delayBetween);

  turnAngle(90, delayBetween);

  driveStraight(30, delayBetween);

  turnAngle(-45, delayBetween);

  driveStraight(20, delayBetween);

  score();


  stopAllDrive();

  */
}



void score() {
  intakeHandler(-12000);
  driveFor(700, 75);
  delay(100);

  rollerT.move_voltage(-12000);
  rollerB.move_voltage(-12000);

  delay(500);
  intakeHandler(0);
  topRoller(0);
  delay(1200);
  topRoller(0);
  midRollers(0);
}
