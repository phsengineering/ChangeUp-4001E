#include "main.h"
#include "subsystems.hpp"
#include <stdio.h>

using namespace pros;

Motor driveRB(11, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_ROTATIONS);
Motor driveRF(12, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_ROTATIONS);
Motor driveLB(20, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_ROTATIONS);
Motor driveLF(19, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_ROTATIONS);

pros::Imu imu_sensor(10);

void leftTPS(double tickDistance) {
  double current = (driveLB.get_position() + driveLF.get_position()) / 2;
}

void rightTPS(double tickDistance) {

}

// X-Drive Code

double timer = 0;

void xDriveStrafe(int y, int x, int rot) {
  y *= 11000.0 / 127.0;
  x *= 11000.0 / 127.0;
  rot *= 11000.0 / 127.0;

  int LF  =  y + x + rot;
  int LB  =  y - x + rot;
  int RF  = -y + x + rot;
  int RB  = -y - x + rot;

  driveLF.move_voltage(LF);
  driveLB.move_voltage(LB);
  driveRF.move_voltage(RF);
  driveRB.move_voltage(RB);
}

void xDriveCorrection(int y, int x, int rot) { // code to make easier for drive (not reccomended for auton)



  y *= 11000.0 / 127.0;
  x *= 11000.0 / 127.0;
  rot *= 11000.0 / 127.0;

  int LF  =  y + x + rot;
  int LB  =  y - x + rot;
  int RF  = -y + x + rot;
  int RB  = -y - x + rot;

  driveLF.move_voltage(LF);
  driveLB.move_voltage(LB);
  driveRF.move_voltage(RF);
  driveRB.move_voltage(RB);
}
// Old Drive Code



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
/*  pros::lcd::initialize();
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
*/
}
