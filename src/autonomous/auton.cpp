#include "main.h"
#include "subsystems.hpp"
#include <stdio.h>
#include <math.h>

using namespace pros;

void autonHandler() {

  flipout();
  delay(500);
  intakeHandler(-12000);

}
