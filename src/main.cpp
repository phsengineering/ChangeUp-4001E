#include "main.h"
#include "subsystems.hpp"
#include <stdio.h>
#include <string>

using namespace pros;

pros::Controller mainController = Controller(E_CONTROLLER_MASTER);


void initialize() {
	init();
	mainController.set_text(0, 0, "4001E");
  imu_sensor.reset();

  double time = pros::millis();
  double iter = 0;

	pros::lcd::set_text(2, "IMU calibrating");

  while (imu_sensor.is_calibrating()) {
    printf("IMU calibrating... %d\n", iter);
		std::string s = std::to_string(1.98-(iter/1000));
		pros::lcd::set_text(3, s);
    iter += 10;
    pros::delay(10);
  }
  printf("IMU is done calibrating (took %d ms)\n", iter - time);
}

double currentTicks, previousTicks;

void disabled() {}

void competition_initialize() {}

void autonomous() {}

void opcontrol() {
	while(true) {

		if(mainController.get_digital(DIGITAL_L2)){ //mid tower
				imuTurn(-90);
		} else if (mainController.get_digital(DIGITAL_L1)) {
				imuTurn(90);
		} else if (mainController.get_digital(DIGITAL_R2)) { //mid tower
				dualDrive(24, 7000);
		} else if (mainController.get_digital(DIGITAL_R1)) {
				double del = 250;
				double spe = 25000;
				dualDrive(36, spe);
				delay(del);
				imuTurn(-90);
				delay(del);
				dualDrive(12, spe);
				delay(del);
				imuTurn(-90);
				delay(del);
				dualDrive(36, spe);
				delay(del);
				imuTurn(-90);
				delay(del);
				dualDrive(12, spe);
				delay(del);
				imuTurn(-90);
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
		delay(2);
}
