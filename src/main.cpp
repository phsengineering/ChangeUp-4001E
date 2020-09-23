#include "main.h"
#include "subsystems.hpp"
#include <stdio.h>

using namespace pros;

pros::Controller mainController = Controller(E_CONTROLLER_MASTER);

void initialize() {
	init();
	mainController.set_text(0, 0, "4001E");
}

double currentTicks, previousTicks;

void disabled() {}

void competition_initialize() {}

void autonomous() {}

void opcontrol() {
	while(true) {

		if(mainController.get_digital(DIGITAL_L2)){ //mid tower
				goDistancePID(24, 10000); //24 inches, 20000 speed
		} else if(mainController.get_digital(DIGITAL_R2)){ //mid tower
			showcasePID(0,0);
		}


			//displayTicks();
			int analogY = mainController.get_analog(E_CONTROLLER_ANALOG_LEFT_Y); // get Y value from left analog stick
			int analogX = mainController.get_analog(E_CONTROLLER_ANALOG_LEFT_X); // get X value from left analog stick
			if(std::abs(analogY) < 16)
			{
				analogX = 127.0 * std::copysign(std::pow(std::abs(analogX / 127.0), 1.4 ), analogX); // make turning less sensitive than driving forward or backwards
			}
			drive(analogY, analogX);
		}

}
