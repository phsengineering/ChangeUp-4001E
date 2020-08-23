#include "main.h"
#include "subsystems.hpp"
#include <stdio.h>

using namespace pros;

void drive(int y, int r)
{
    //Scale up y and r from 127 to 12000
    y *= 11000.0 / 127.0;
    r *= 11000.0 / 127.0; //double check math

    driveLF.move_voltage(y + r);
    driveLB.move_voltage(y + r);
    driveRF.move_voltage(y - r);
    driveRB.move_voltage(y - r);
}

void turnDrive(double y)
{
    y *= 11000.0 / 127.0;

    driveLF.move_voltage(y);
    driveLB.move_voltage(y);
    driveRF.move_voltage(-y);
    driveRB.move_voltage(-y);
}


void autonDrive(double y, double max)
{
  ///double max = 7000;
  y *= 11000.0 / 127.0;
  if (y > max) {
    y = max;
  }
  if (y < 0 && y < -fabs(max)){
    y = -max;
  }

    driveLF.move_voltage(y);
    driveLB.move_voltage(y);
    driveRF.move_voltage(y);
    driveRB.move_voltage(y);

}
