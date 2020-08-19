#include "main.h"
#include <stdio.h>

using namespace pros;

Motor driveRF(1, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_ROTATIONS);
Motor driveRB(2, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_ROTATIONS);
Motor driveLF(3, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_ROTATIONS);
Motor driveLB(4, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_ROTATIONS);

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}


void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
}

void disabled() {}

void competition_initialize() {}

void autonomous() {}


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

void opcontrol() {
	pros::Controller mainController = Controller(E_CONTROLLER_MASTER);

	goDistancePID(27); // GO 10 INCHES







/*
	while(true) {


			int analogY = mainController.get_analog(E_CONTROLLER_ANALOG_LEFT_Y); // get Y value from left analog stick
			int analogX = mainController.get_analog(E_CONTROLLER_ANALOG_LEFT_X); // get X value from left analog stick
			if(std::abs(analogY) < 16)
			{
				analogX = 127.0 * std::copysign(std::pow(std::abs(analogX / 127.0), 1.4 ), analogX); // make turning less sensitive than driving forward or backwards
			}
			drive(analogY, analogX); // actual drive with these paramaters
		//	printf("Motor Position: %lf\n", driveLF.get_position());

		}
		*/
}
