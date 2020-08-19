#include "main.h"
#include "subsystems.hpp"
#include <stdio.h>

using namespace pros;

Motor driveRF(1, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_ROTATIONS);
Motor driveRB(2, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_ROTATIONS);
Motor driveLF(3, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_ROTATIONS);
Motor driveLB(4, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_ROTATIONS);


void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");
}

void disabled() {}

void competition_initialize() {}

void autonomous() {}

void opcontrol() {
	pros::Controller mainController = Controller(E_CONTROLLER_MASTER);
printf("\033[1;34m[Welcome to Team 4001E]\033[0m\n");
	while(true) {

		if(mainController.get_digital(DIGITAL_L2)){ //mid tower
			goDistancePID(27);
		} else if(mainController.get_digital(DIGITAL_R2)){ //mid tower
			turnDrive(20);
			//turnAnglePID(90);
		}


			int analogY = mainController.get_analog(E_CONTROLLER_ANALOG_LEFT_Y); // get Y value from left analog stick
			int analogX = mainController.get_analog(E_CONTROLLER_ANALOG_LEFT_X); // get X value from left analog stick
			if(std::abs(analogY) < 16)
			{
				analogX = 127.0 * std::copysign(std::pow(std::abs(analogX / 127.0), 1.4 ), analogX); // make turning less sensitive than driving forward or backwards
			}
			drive(analogY, analogX); // actual drive with these paramaters
		//	printf("Motor Position: %lf\n", driveLF.get_position());

		}

}
