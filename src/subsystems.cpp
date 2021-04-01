#include "main.h"
#include "subsystems.hpp"
#include <stdio.h>

using namespace pros;

Motor driveRB(8, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_ROTATIONS);
Motor driveRF(9, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_ROTATIONS);
Motor driveLB(5, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_ROTATIONS);
Motor driveLF(4, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_ROTATIONS);

Motor intakeL(7, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_ROTATIONS);
Motor intakeR(10, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_ROTATIONS);

Motor rollerB(6, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_ROTATIONS);
Motor rollerT(3, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_ROTATIONS);

double timer = 0;

ADIAnalogIn sensorY ('X');
ADIAnalogIn sensorX ('Z');

ADIEncoder rightEncoder ('G', 'H', false);
ADIEncoder middleEncoder ('A', 'B', false);
ADIEncoder leftEncoder ('D', 'C', true);

double valY;
double valX;

Imu thatIMU(1);
Imu thatIMU2(11);

Controller mainController = Controller(E_CONTROLLER_MASTER);

void normalDrive(int y, int x) {
  y *= 11000.0 / 127.0;
  x *= (11000.0 / -127.0);

  driveRF.move_voltage((y + x)/1);
  driveRB.move_voltage((y + x)/1);
  driveLF.move_voltage(y - x);
  driveLB.move_voltage(y - x);
}

void fbauton(double y) {
  y *= 11000.0 / 127.0;

  driveRF.move_voltage(y/1.00);
  driveRB.move_voltage(y/1.00);
  driveLF.move_voltage(y/1.00);
  driveLB.move_voltage(y/1.00);
}

void fbautonBACK(double y) {
  y *= 11000.0 / 127.0;

  driveRF.move_voltage(y/1.00);
  driveRB.move_voltage(y/1.00);
  driveLF.move_voltage(y/1.00);
  driveLB.move_voltage(y/1.00);
}

void autonTurn(double y) {
  y *= 11000.0 / 127.0;

  driveLF.move_voltage(y);
  driveLB.move_voltage(y);
  driveRF.move_voltage(-y);
  driveRB.move_voltage(-y);
}

void driveFor(double seconds, double power) {
  double x = 0;
  double y = power;
  y *= 11000.0 / 127.0;

  driveRF.move_voltage((y + x)/1);
  driveRB.move_voltage((y + x)/1);
  driveLF.move_voltage(y - x);
  driveLB.move_voltage(y - x);

  delay(seconds);

  stopAllDrive();
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

void wireless() {
  double previousX = valX;
  double previousY = valY;
  valY = ((sensorY.get_value()-15) / 10.6299) - 127;
  valX = ((sensorX.get_value()-15) / 10.6299) - 127;

  if (fabs(valY) <= 50) {
    valY = 0;
  }
  if (fabs(valY - previousY) <= 10) {
    valY = previousY;
  }

  if (fabs(valX) <= 50) {
    valX = 0;
  }
  if (fabs(valX - previousX) <= 10) {
    valX = previousX;
  }
  normalDrive(valY, valX);
  printf("   target: %lf\n", valX);
}

int current = -1;

std::string autons[6] =
{
 "Red Left [Corner/Side]",
 "Red Left [Corner/Side/Middle]",
 "Red Right [Corner/Side]",
 "Red Right [Corner/Side/Middle]",
 "Red Just Score 1",
 "Blue Left [Corner/Side]",
 "Blue Left [Corner/Side/Middle]",
 "Blue Right [Corner/Side]",
 "Blue Right [Corner/Side/Middle]",
 "Blue Just Score 1",
 "Prog Skills"
};


void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
    current++;
    if (current == 6) {
      current = 0;
    }
  	lcd::set_text(3, autons[current]); // replace with pros lcd print // replace with pros lcd print
    mainController.set_text(0, 0, autons[current]);
}

void init() {
  lcd::initialize();
  lcd::set_text(0, "VRC Team 4001E Change Up 2020-21");
  lcd::set_text(6, "Press the center button below to");
  lcd::set_text(7, "cycle through autonomous choices");

  lcd::register_btn1_cb(on_center_button);

  thatIMU.reset();
  thatIMU2.reset();

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
