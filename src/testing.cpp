#include "main.h"
#include "subsystems.hpp"
#include <stdio.h>

using namespace pros;

#define QUAD_TOP_PORT 'C'
#define QUAD_BOTTOM_PORT 'D'

pros::ADIEncoder encoder (QUAD_TOP_PORT, QUAD_BOTTOM_PORT, true);

void testingEncoders() {
  printf("%lf \n", encoder.get_value());
  delay(100);
}
