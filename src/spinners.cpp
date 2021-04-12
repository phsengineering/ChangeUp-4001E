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
  delay(4000);
  intakeL.move_voltage(0);
}

void score() {
  rollerT.move_voltage(-12000);
  rollerB.move_voltage(-12000);
  delay(650);
  rollerT.move_voltage(0);
  rollerB.move_voltage(0);
}

void score2() {
  rollerB.move_voltage(-12000);
  rollerT.move_voltage(-12000);
  delay(550);
  rollerB.move_voltage(12000);
  rollerT.move_voltage(12000);
  delay(650);
  rollerB.move_voltage(-12000);
  rollerT.move_voltage(-12000);
  delay(600);
  rollerHandler(0);
}
