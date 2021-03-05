#include "main.h"
#include "subsystems.hpp"
#include <stdio.h>
#include <math.h>

using namespace pros;

double delayBetween = 250;

void autonHandler() {

  flipout();

  intakeHandler(-12000);
  driveStraight(36, delayBetween); // drive to first ball on edge of tile

  intakeHandler(0);
  turnAngle(-73, delayBetween); // turn towards goal

  driveStraight(18, 0); // drive towards goal
  score(); //[A1]

  driveStraight(-30, delayBetween); //back up from goal

  turnAngle(135, delayBetween); // turn towards next ball

  intakeHandler(-12000);
  driveStraight(50, delayBetween); // drive towards next ball while intaking

  intakeHandler(0);
  turnAngle(-90, delayBetween); // turn towards goal

  score(); //[A2]

  driveStraight(-30, delayBetween); // back up from goal

  turnAngle(101, delayBetween); //turn towards next ball

  intakeHandler(-12000);
  driveStraight(50, delayBetween); // drive towards next ball

  intakeHandler(0);

  driveStraight(-10, delayBetween);

  turnAngle(-101, delayBetween);

  driveStraight(15, delayBetween);

  score(); //[A3]

  driveStraight(-15, delayBetween);

  turnAngle(160, delayBetween);

  intakeHandler(-12000);
  driveStraight(50, delayBetween);

  intakeHandler(0);
  turnAngle(-130, delayBetween);








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
