#include "main.h"
#include "subsystems.hpp"
#include <stdio.h>

using namespace pros;

Motor driveRB(11, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_ROTATIONS);
Motor driveRF(20, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_ROTATIONS);
Motor driveLB(19, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_ROTATIONS);
Motor driveLF(18, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_ROTATIONS);

Motor intakeL(1, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_ROTATIONS);
Motor intakeR(2, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_ROTATIONS);

Motor rollerB(15, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_ROTATIONS);
Motor rollerT(9, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_ROTATIONS);

double timer = 0;

pros::Imu thatIMU(7);

void normalDrive(int y, int x) {
  y *= 11000.0 / 127.0;
  x *= 11000.0 / -127.0;

  driveRF.move_voltage((y + x)/1.08);
  driveRB.move_voltage((y + x)/1.08);
  driveLF.move_voltage(y - x);
  driveLB.move_voltage(y - x);
}

void intakeHandler(int power) {
  intakeL.move_voltage(power);
  intakeR.move_voltage(power);
}

void midRollers(int power) {
  rollerB.move_voltage(power);
}

void topRoller(int power) {
  rollerT.move_voltage(power);
}

void autonTurn(double y) {
  y *= 11000.0 / 127.0;
//    x *= 11000.0 / 127.0;

  driveLF.move_voltage(y);
  driveLB.move_voltage(y);
  driveRF.move_voltage(-y);
  driveRB.move_voltage(-y);
}

void turnDrive(double y)
{
    y *= 11000.0 / 127.0;

    double cor = 1;

    driveLF.move_voltage(y/cor);
    driveLB.move_voltage(y/cor);
    driveRF.move_voltage(-y*cor*5);
    driveRB.move_voltage(-y*cor*5);
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

void autonDriveVary(double left, double right, double max)
{
  ///double max = 7000;
  left *= 11000.0 / 127.0;
  if (left > max) {
    left = max;
  }
  if (left < 0 && left < -fabs(max)){
    left = -max;
  }

  right *= 11000.0 / 127.0;
  if (right > max) {
    right = max;
  }
  if (right < 0 && right < -fabs(max)){
    right = -max;
  }

    driveLF.move_voltage(left);
    driveLB.move_voltage(left);
    driveRF.move_voltage(right);
    driveRB.move_voltage(right);
}

void leftDrive(double y, double max) {
  y *= 11000.0 / 127.0;
  if (y > max) {
    y = max;
  }
  if (y < 0 && y < -fabs(max)){
    y = -max;
  }

    driveLF.move_voltage(y);
    driveLB.move_voltage(y);
}

void rightDrive(double y, double max) {
  y *= 11000.0 / 127.0;
  if (y > max) {
    y = max;
  }
  if (y < 0 && y < -fabs(max)){
    y = -max;
  }

    driveRF.move_voltage(y/1.075);
    driveRB.move_voltage(y/1.075);
}

void stopAllDrive() {
  driveLF.move_velocity(0);
  driveRF.move_velocity(0);
  driveLB.move_velocity(0);
  driveRB.move_velocity(0);
}

void tareAll() {
  driveLF.tare_position();
  driveRF.tare_position();
  driveLB.tare_position();
  driveRB.tare_position();
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
