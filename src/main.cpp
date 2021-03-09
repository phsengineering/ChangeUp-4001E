#include "main.h"
#include "subsystems.hpp"
#include <stdio.h>
#include <string>

using namespace pros;

pros::Controller mainController = Controller(E_CONTROLLER_MASTER);

void initialize() {
		init();
		mainController.set_text(0, 0, "where's gabe");

		thatIMU.reset();
		thatIMU2.reset();
}


void on_center_button() {
  static bool pressed = false;
  pressed = !pressed;
  if (pressed) {
    pros::lcd::set_text(2, "I was pressed!");
  } else {
    pros::lcd::clear_line(2);
  }
}



double currentTicks, previousTicks;

void disabled() {}

void competition_initialize() {}

void autonomous() {
	autonHandler();
}

int wireless = 0;

void opcontrol() {
	while(true) {

		if(mainController.get_digital(DIGITAL_L2)){ //mid tower
			rollerT.move_voltage(-12000);
			rollerB.move_voltage(-12000);
		} else if (mainController.get_digital(DIGITAL_L1)) {
			rollerT.move_voltage(12000);
			rollerB.move_voltage(12000);
		} else {
			rollerT.move_voltage(0);
			rollerB.move_voltage(0);
		}


		if (mainController.get_digital(DIGITAL_R1)) {
			intakeL.move_voltage(12000);
			intakeR.move_voltage(12000);
		} else if (mainController.get_digital(DIGITAL_R2)) {
			intakeL.move_voltage(-12000);
			intakeR.move_voltage(-12000);
		} else {
			intakeL.move_voltage(0);
			intakeR.move_voltage(0);
		}


		if(mainController.get_digital(DIGITAL_A)) {
		  autonHandler();
		}

		if(mainController.get_digital(DIGITAL_UP)) {
		  rollerB.move_voltage(-12000);
		}

		if(mainController.get_digital(DIGITAL_DOWN)) {
		  flipout();
		}

			int analogY = mainController.get_analog(E_CONTROLLER_ANALOG_LEFT_Y); // get Y value from left analog stick
			int analogX = mainController.get_analog(E_CONTROLLER_ANALOG_LEFT_X); // get X value from right analog stick
			if(std::abs(analogY) < 16)
			{
				analogX = 127.0 * std::copysign(std::pow(std::abs(analogX / 127.0), 1.4 ), analogX); // make turning less sensitive than driving forward or backwards
			}
			normalDrive(analogY, analogX);

			delay(10);
		}

}
