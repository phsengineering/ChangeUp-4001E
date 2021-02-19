#include "main.h"
#include "subsystems.hpp"
#include <stdio.h>
#include <math.h>

using namespace pros;

double delayBetween = 250;

void autonHandler() {

  intakeHandler(-12000);
  rollerB.move_voltage(-12000);
  thatIMU.reset();

  delay(2005);

  driveStraight(25.5, delayBetween); //23.5
  intakeHandler(0);
  rollerB.move_voltage(0);

  turnAngle(-135, delayBetween);

  driveStraight(27.5, 100);

  score();

  driveStraight(-30, delayBetween);

  turnAngle(-45, 0);

  intakeHandler(12000);
  rollerT.move_voltage(12000);
  rollerB.move_voltage(12000);

  delay(1000);
  rollerT.move_voltage(0);
  turnAngle(90, 0);
  intakeHandler(-12000);
  rollerB.move_voltage(-12000);
  driveStraight(25, delayBetween);
  rollerT.move_voltage(0);
  rollerB.move_voltage(0);
  intakeHandler(0);
  driveStraight(-15, delayBetween);
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

  stopAllDrive(); */
}



void score() {
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
}
