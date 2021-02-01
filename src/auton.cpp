#include "main.h"
#include "subsystems.hpp"
#include <stdio.h>
#include <math.h>

using namespace pros;

void autonHandler() {
  intakeL.move_voltage(-12000);
  intakeR.move_voltage(-12000);
  midRollers(12000);
  asdf(15);
  delay(1000);
  xDriveTurn(-120);
  rollerT.move_voltage(-12000);
  rollerB.move_voltage(-12000);
  delay(250);
  normalDrive(80,0);
  delay(2000);
  stopAllDrive();
  rollerT.move_voltage(-12000);
  rollerB.move_voltage(-12000);
  delay(1000);
  topRoller(0);
  intakeHandler(0);
  midRollers(0);
}
