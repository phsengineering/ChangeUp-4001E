#include "main.h"
#include "subsystems.hpp"
#include <stdio.h>
#include <string>

using namespace pros;

Vision vision_sensor (12);

vision_object_s_t object_arr[4];

void initialize() {init();}

void disabled() {}

void competition_initialize() {}

void autonomous() {autonHandler();}

int	visionCount = 0,
		globalCount = 0,
		count = 0,
		visionColor;

double intakeOffset = 1.5;

void opcontrol() {
	while(true) {
		vision_sensor.read_by_size(0, 4, object_arr);
		if(mainController.get_digital(DIGITAL_L2)){
			if(current == 0 || current == 1 || current == 2 || current == 3 || current == 4 || current == -1) {
				visionColor = 1;
			} else {
				visionColor = 2;
			}
			if (object_arr[0].height >= 80 && object_arr[0].width >= 80 && object_arr[0].signature == visionColor && visionCount <= 750) {
				delay(50);
				rollerT.move_voltage(12000);
				rollerB.move_voltage(12000);
				visionCount++;
			} else {
			  rollerT.move_voltage(-12000);
				rollerB.move_voltage(-12000);
				visionCount = 0;
			}
			rollerB.move_voltage(-12000);
		} else if (mainController.get_digital(DIGITAL_L1)) {
			rollerT.move_voltage(12000);
			rollerB.move_voltage(12000);
		} else {
			if (mainController.get_digital(DIGITAL_UP)) {
				rollerT.move_voltage(-12000);
				rollerB.move_voltage(-12000);
			} else {
				rollerT.move_voltage(0);
				rollerB.move_voltage(0);
			}
		}

		if (mainController.get_digital(DIGITAL_UP)) {
			rollerT.move_voltage(-12000);
			rollerB.move_voltage(-12000);
		}

		if (mainController.get_digital(DIGITAL_R1)) {
			intakeL.move_voltage(12000 / intakeOffset);
			intakeR.move_voltage(12000 / intakeOffset);
		} else if (mainController.get_digital(DIGITAL_R2)) {
			intakeL.move_voltage(-12000 / intakeOffset);
			intakeR.move_voltage(-12000 / intakeOffset);
		} else {
			intakeL.move_voltage(0);
			intakeR.move_voltage(0);
		}

		if(mainController.get_digital(DIGITAL_A)) {
		//	okapiDrive();
			//autonHandler();
			driveStraight(24, 0);
		//auton3balls(true);
		}

		if(mainController.get_digital(DIGITAL_DOWN)) {
		  flipout();
		}

		int analogY = mainController.get_analog(E_CONTROLLER_ANALOG_LEFT_Y); // get Y value from left analog stick
		int analogX = mainController.get_analog(E_CONTROLLER_ANALOG_LEFT_X); // get X value from right analog stick
		if(std::abs(analogY) < 16) {
				analogX = 127.0 * std::copysign(std::pow(std::abs(analogX / 127.0), 1.4), analogX); // make turning less sensitive than driving forward or backwards
		}
		normalDrive(analogY, analogX);

		if (globalCount == 1000) {
			if (driveRF.is_over_temp() || driveRB.is_over_temp() || driveLF.is_over_temp() || driveLB.is_over_temp()) {
				mainController.rumble("- .");
			}
			std::string temp = std::to_string((driveLF.get_temperature()+driveLB.get_temperature()+driveRB.get_temperature()+driveRF.get_temperature())/4);
			mainController.set_text(0, 0, temp.c_str());
			globalCount = 0;
		}
		delay(2);
		globalCount++;
	}
}
