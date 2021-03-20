#include "main.h"
#include "subsystems.hpp"
#include <stdio.h>
#include <string>

using namespace pros;

pros::Controller mainController = Controller(E_CONTROLLER_MASTER);
pros::Vision vision_sensor (12);
pros::ADIAnalogIn sensorY ('F');
//pros::ADIAnalogIn sensorX ('E');

pros::ADIAnalogOut flashlight ('E');

#define NUM_VISION_OBJECTS 4

vision_object_s_t object_arr[NUM_VISION_OBJECTS];

double valY;
double valX;

void initialize() {
		init();

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
int count = 0;
int globalCount = 0;

void opcontrol() {
	while(true) {
		flashlight.set_value(999999);
		vision_sensor.read_by_size(0, NUM_VISION_OBJECTS, object_arr);
		if (driveRF.is_over_temp() || driveRB.is_over_temp() || driveLF.is_over_temp() || driveLB.is_over_temp()) {
			mainController.rumble("- .");
		}
		if(mainController.get_digital(DIGITAL_L2)){ //mid tower
			if (object_arr[0].height >= 80 && object_arr[0].width >= 80 && object_arr[0].signature == 1 && count <= 750) {
				delay(50);
				rollerT.move_voltage(12000);
				rollerB.move_voltage(12000);
				count++;
			} else {
			  rollerT.move_voltage(-12000);
				rollerB.move_voltage(-12000);
				count = 0;
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
		} else {
		//	rollerT.move_voltage(0);
		//	rollerB.move_voltage(0);
		}

double offset = 1.5;

		if (mainController.get_digital(DIGITAL_R1)) {
			intakeL.move_voltage(12000 / offset);
			intakeR.move_voltage(12000 / offset);
		} else if (mainController.get_digital(DIGITAL_R2)) {
			intakeL.move_voltage(-12000 / offset);
			intakeR.move_voltage(-12000 / offset);
		} else {
			intakeL.move_voltage(0);
			intakeR.move_voltage(0);
		}


		if(mainController.get_digital(DIGITAL_A)) {
		  autonHandler();
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
	/*		double previousY = valY;
			double previousX = valX;
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

			printf("   target: %lf\n", valX); */
		//	driveLF.get_temperature()
		if (globalCount == 1000) {
			std::string temp = std::to_string(driveLF.get_temperature());
			mainController.set_text(0, 0, temp.c_str());
			globalCount = 0;
		}
			delay(1);
			globalCount++;
		}

}
