#include "main.h"
#include "subsystems.hpp"
#include <stdio.h>
#include <math.h>

using namespace pros;

double delayBetween = 250;

void autonHandler() {

  turnAngle(180);

/*  intakeHandler(-12000);
  rollerB.move_voltage(-12000);
  thatIMU.reset();

  delay(2005);

  driveStraight(28.5);
  intakeHandler(0);
  rollerB.move_voltage(0);

  delay(delayBetween);
  turnAngle(-137);

  delay(delayBetween);

  driveStraight(27.5);
  delay(100);
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
  driveStraight(-35);
  delay(delayBetween);
  turnAngle(-45);

  intakeHandler(12000);
  rollerT.move_voltage(12000);
  rollerB.move_voltage(12000);

  delay(1000);
  rollerT.move_voltage(0);
  turnAngle(90);
  intakeHandler(-12000);
  rollerB.move_voltage(-12000);
  driveStraight(23.5);
  delay(delayBetween);
  rollerT.move_voltage(0);
  rollerB.move_voltage(0);
  intakeHandler(0);
  driveStraight(-23.5);
  delay(delayBetween);
  turnAngle(90);
  delay(delayBetween);
  driveStraight(45);
  delay(delayBetween);
  turnAngle(-90);
  delay(delayBetween);

  driveStraight(23);
  intakeHandler(-12000);
  rollerT.move_voltage(-12000);
  rollerB.move_voltage(-12000);

  delay(1200);

  intakeHandler(0);
  rollerT.move_voltage(0);
  rollerB.move_voltage(0);

  stopAllDrive(); */
}
