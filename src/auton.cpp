#include "main.h"
#include "subsystems.hpp"
#include <stdio.h>
#include <math.h>

using namespace pros;

double delayBetween = 100;

void autonHandler() {
  flipout();
  intakeHandler(-12000);
  driveStraight(34.5, delayBetween); // drive to first ball on edge of tile

  intakeHandler(0);
  turnAngle(68, delayBetween); // turn towards goal

  driveStraight(13, 0); // drive towards goal
  score(); //[A1]

  driveStraight(-8, delayBetween+50); //back up from goal
  rollerHandler(0);
  intakeHandler(0);


  turnAngle(-163.5, delayBetween); // turn towards next ball
  intakeHandler(-12000);

  driveStraight(56, delayBetween); // drive towards next ball while intaking

  turnAngle(113, delayBetween);

  delay(50);
  //rollerB.move_velocity(-12000);
  driveStraight(25.5, delayBetween);
  intakeHandler(0);

  score2();
//  score(); //[A2]

  driveStraight(-18.5, delayBetween); // back up from goal

  turnAngle(-92, delayBetween); //turn towards next ball

  intakeHandler(-12000);
  rollerT.move_voltage(0);
  rollerB.move_voltage(-2000);
  driveStraight(51.5, delayBetween); // drive towards next ball

  intakeHandler(0);

  driveStraight(-18.5, delayBetween);

  turnAngle(45, delayBetween);

  driveStraight(15, delayBetween);

  score(); //[A3]

  driveStraight(-15, delayBetween);

  turnAngle(-154, delayBetween);

  intakeHandler(-12000);
  driveStraight(54, delayBetween);

  intakeHandler(0);
  turnAngle(115.5, delayBetween);

  driveStraight(20, delayBetween);

  score2();
  rollerHandler(0);

  driveStraight(-15, delayBetween);

  turnAngle(-90, delayBetween);

  intakeHandler(-12000);
  driveStraight(30, delayBetween);

  intakeHandler(0);
  turnAngle(-45, delayBetween);

  driveStraight(10, delayBetween);

  score(); //[C3]

  driveStraight(-20, delayBetween);

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
