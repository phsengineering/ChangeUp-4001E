
#include "main.h"
#include "subsystems.hpp"
#include <stdio.h>

using namespace pros;

#define QUAD_TOP_PORT 'G'
#define QUAD_BOTTOM_PORT 'H'

pros::ADIEncoder encoder (QUAD_TOP_PORT, QUAD_BOTTOM_PORT, true);

double enc = 0;

void testingEncoders() {
  enc = encoder.get_value();
  printf("%lf \n", enc);
}
