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

void turnDrive(int y)
{
    //y *= 11000.0 / 127.0;

    driveLF.move_voltage(y);
    driveLB.move_voltage(y);
    driveRF.move_voltage(y);
    driveRB.move_voltage(y);
}
