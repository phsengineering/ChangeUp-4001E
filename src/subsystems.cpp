#include "main.h"
#include "subsystems.hpp"
#include <stdio.h>

using namespace pros;



Motor driveRF(1, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_ROTATIONS);
Motor driveRB(2, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_ROTATIONS);
Motor driveLF(3, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_ROTATIONS);
Motor driveLB(4, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_ROTATIONS);


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


void driveVelLeft(double speed)
{
    driveLF.move_velocity(speed);
    driveLB.move_velocity(speed);
}

void driveVelRight(double speed)
{
    driveRF.move_velocity(speed);
    driveRB.move_velocity(speed);
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





void init() {
  pros::lcd::initialize();
  pros::lcd::set_text(1, "4001E");

  printf("\033[1;31m____________/\\\\\\____        _____/\\\\\\\\\\\\\\____        _____/\\\\\\\\\\\\\\____        ______/\\\\\\_        __/\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\_        \033[0m\n");
  printf("\033[1;31m __________/\\\\\\\\\\____        ___/\\\\\\/////\\\\\\__        ___/\\\\\\/////\\\\\\__        __/\\\\\\\\\\\\\\_        _\\/\\\\\\///////////__       \033[0m\n");
  printf("\033[1;31m  ________/\\\\\\/\\\\\\____        __/\\\\\\____\\//\\\\\\_        __/\\\\\\____\\//\\\\\\_        _\\/////\\\\\\_        _\\/\\\\\\_____________      \033[0m\n");
  printf("\033[1;31m   ______/\\\\\\/\\/\\\\\\____        _\\/\\\\\\_____\\/\\\\\\_        _\\/\\\\\\_____\\/\\\\\\_        _____\\/\\\\\\_        _\\/\\\\\\\\\\\\\\\\\\\\\\_____     \033[0m\n");
  printf("\033[1;31m    ____/\\\\\\/__\\/\\\\\\____        _\\/\\\\\\_____\\/\\\\\\_        _\\/\\\\\\_____\\/\\\\\\_        _____\\/\\\\\\_        _\\/\\\\\\///////______    \033[0m\n");
  printf("\033[1;31m     __/\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\_        _\\/\\\\\\_____\\/\\\\\\_        _\\/\\\\\\_____\\/\\\\\\_        _____\\/\\\\\\_        _\\/\\\\\\_____________   \033[0m\n");
  printf("\033[1;31m      _\\///////////\\\\\\//__        _\\//\\\\\\____/\\\\\\__        _\\//\\\\\\____/\\\\\\__        _____\\/\\\\\\_        _\\/\\\\\\_____________  \033[0m\n");
  printf("\033[1;31m       ___________\\/\\\\\\____        __\\///\\\\\\\\\\\\\\/___        __\\///\\\\\\\\\\\\\\/___        _____\\/\\\\\\_        _\\/\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\_ \033[0m\n");
  printf("\033[1;31m        ___________\\///_____        ____\\///////_____        ____\\///////_____        _____\\///_         _\\///////////////__\033[0m\n");
}
