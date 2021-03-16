#include "main.h"
#include "subsystems.hpp"
#include <stdio.h>

using namespace pros;

void rollerHandler(double power) {
  power *= 12000.0 / 100.0;

  rollerT.move_voltage(power);
  rollerB.move_voltage(power);
}

void intakeHandler(double power) {
  intakeL.move_voltage(power);
  intakeR.move_voltage(power);
}


void flipout() {
  intakeL.move_voltage(-12000);
  delay(100);
  intakeL.move_voltage(0);
}

void score() {
  driveFor(700, 75);
  rollerT.move_voltage(-12000);
  rollerB.move_voltage(-12000);
  delay(500);
  rollerT.move_voltage(0);
  rollerB.move_voltage(0);

/*  intakeHandler(-12000);
  driveFor(700, 75);
  delay(100);

  rollerT.move_voltage(-12000);
  rollerB.move_voltage(-12000);

  delay(500);
  intakeHandler(0);
  topRoller(0);
  delay(1200);
  topRoller(0);
  midRollers(0); */
}

void score2() {
  driveFor(700, 75);
  delay(200);
  rollerB.move_voltage(-12000);
  rollerT.move_voltage(-12000);
  delay(650);
  rollerB.move_voltage(12000);
  rollerT.move_voltage(12000);
  delay(500);
  rollerB.move_voltage(-12000);
  rollerT.move_voltage(-12000);
  delay(500);
  rollerHandler(0);
}
