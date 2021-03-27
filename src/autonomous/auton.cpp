#include "main.h"
#include "subsystems.hpp"
#include <stdio.h>
#include <math.h>

using namespace pros;

double delayBetween = 150;

void autonHandler() {
  flipout();
  delay(500);
  intakeHandler(-12000);
  driveStraight(36, delayBetween); // drive to first ball on edge of tile

  intakeHandler(0);
  turnAngle(67.5, delayBetween); // turn towards goal

  driveFor(800, 65);
  score(); //[A1]
  ///////////////////////////////////////////////////////////////////////

  driveStraight(-8, delayBetween+50); //back up from goal
  rollerHandler(0);
  intakeHandler(0);

  turnAngle(-155.75, delayBetween); // turn towards next ball
  intakeHandler(-12000);

  driveStraight(63, delayBetween); // drive towards next ball while intaking

  turnAngle(116, delayBetween);

  delay(50);
  driveStraight(23, delayBetween);
  intakeHandler(0);

  driveFor(700, 65);
  score2(); //[A2]
  //////////////////////////////////////////////////////////////////////////

  driveStraight(-18.25, delayBetween); // back up from goal

  turnAngle(-91.1, delayBetween); //turn towards next ball

  intakeHandler(-12000);
  rollerT.move_voltage(0);
  rollerB.move_voltage(-2000);
  driveStraight(48, delayBetween); // drive towards next ball

  intakeHandler(0);

  driveStraight(-10.0, delayBetween);

  turnAngle(43, delayBetween);

  driveStraight(18.5, delayBetween);

  driveFor(700, 65);
  score(); //[A3]
  ////////////////////////////////////////////////////////////////////////////

  driveStraight(-15, delayBetween);

  turnAngle(-163.5, delayBetween);

  intakeHandler(-12000);
  driveStraight(56, delayBetween);

  intakeHandler(0);

  driveStraight(-6.5, delayBetween);

  turnAngle(103, delayBetween);

  driveStraight(20, delayBetween);

  driveFor(700, 65);
  score(); //[B3]
  ///////////////////////////////////////////////////////////////////////////

  driveStraight(-7, delayBetween);

  turnAngle(-85, delayBetween);

  intakeHandler(-12000);
  driveStraight(43, delayBetween);

  intakeHandler(0);
  turnAngle(25, delayBetween);

  driveStraight(7, delayBetween);

  driveFor(700, 75);
  score(); //[C3]
  ////////////////////////////////////////////////////////////////////////////
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
