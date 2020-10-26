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

  while (imu_sensor.is_calibrating()) {
    printf("IMU calibrating... %d\n", iter);
		std::string s = std::to_string(1.98-(iter/1000));
		pros::lcd::set_text(3, s);
    iter += 10;
    pros::delay(10);
  }
  printf("IMU is done calibrating (took %d ms)\n", iter - time);

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

void autonomous() {}

int wireless = 0;

void opcontrol() {
	while(true) {

		if(mainController.get_digital(DIGITAL_L2)){ //mid tower
				xDriveTurn(90);
		} else if (mainController.get_digital(DIGITAL_L1)) {
				xDriveTurn(-90);
		} else if (mainController.get_digital(DIGITAL_R2)) { //mid tower
				xDriveFB(20);
		} else if (mainController.get_digital(DIGITAL_R1)) {
				double del = 650;
				double spe = 25000;
				xDriveFB(15);
				delay(del);
				xDriveTurn(-90);
				delay(del);
				xDriveFB(15);
				delay(del);
				xDriveTurn(-90);
				delay(del);
				xDriveFB(15);
				delay(del);
				xDriveTurn(-90);
				delay(del);
				xDriveFB(15);
				delay(del);
				xDriveTurn(-90);
		}


			//displayTicks();
			int analogY = mainController.get_analog(E_CONTROLLER_ANALOG_LEFT_Y); // get Y value from left analog stick
			int rotate = mainController.get_analog(E_CONTROLLER_ANALOG_LEFT_X); // get X value from left analog stick
			int analogX = mainController.get_analog(E_CONTROLLER_ANALOG_RIGHT_X); // get X value from right analog stick
			if(std::abs(analogY) < 16)
			{
				analogX = 127.0 * std::copysign(std::pow(std::abs(analogX / 127.0), 1.4 ), analogX); // make turning less sensitive than driving forward or backwards
			}
			xDriveStrafe(analogY, analogX, rotate);


						printf("%lf,", imu_sensor.get_rotation());
					 printf("%lf\n", imu_sensor.get_heading());

					 delay(10);
		}

}
