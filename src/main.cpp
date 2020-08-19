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

void goDistance(double distance) {
	double ticksPerRevolution = 1.7;
	double wheelDiameter = 3.25;

	double wheelCircumference = wheelDiameter * M_PI;
	double revolutionsNeeded = distance / wheelCircumference;

		while (driveLF.get_position() <= (ticksPerRevolution * revolutionsNeeded)) {
			drive(25, 0);
			printf("Motor Position: %lf\n", driveLF.get_position());
		}

		while(driveLF.get_position() > (ticksPerRevolution * revolutionsNeeded)) {
			drive(-25, 0);
			printf("Motor Position: %lf\n", driveLF.get_position());
		}
		drive(0,0);
}

void goDistancePID(double distance) {
		driveLF.tare_position();
    driveRF.tare_position();
    driveLB.tare_position();
    driveRB.tare_position();

    double TARGET = driveLF.get_position() + distance;
    double HALFWAY = driveLF.get_position() + distance / 4;

    double currentValue = driveLF.get_position();
    double currentError = TARGET - currentValue;
    double previousError = 0;

		printf("Current Value: %lf\n", currentValue);
		printf("Current Error: %lf\n", currentError);

    bool accel = true;

    double kP  =  3.000;
    double kI  =  0.000;
    double kD  =  12.000;

		double acceptableError = 0.05;

    double maxRate = 90;

    while(fabs(currentError) > acceptableError) {
			printf("currentError: %lf", currentError);
        if(distance > 0 && currentValue > HALFWAY)
            accel = false;
        else if(distance < 0 && currentValue < HALFWAY)
            accel = false;

        double p  = kP * currentError;
        double i  = kI;
        double d  = kD * (currentError - previousError);

        double command = p + i + d;

        if(fabs(command) > maxRate) {
            if(command > 0)
                command = maxRate;
            else
                command = -maxRate;
        }
				printf("   command: %lf", command);

				if (fabs(command) < 1) {

					if (command > 0) {
						drive(15,0);
					} else {
						drive(-15,0);
					}
					pros::delay(20);
				} else{
					drive(command*20, 0);
				}

        pros::delay(20);

        if(accel) {
            if(maxRate < 120)
            maxRate += 10;
        }

        currentValue = driveLF.get_position();
        previousError = currentError;
        currentError = TARGET - currentValue;

				printf("   position: %lf", currentValue);
				printf("   target: %lf\n", TARGET);

    }

    driveLF.move_velocity(0);
    driveRF.move_velocity(0);
    driveLB.move_velocity(0);
    driveRB.move_velocity(0);


}

void opcontrol() {
	pros::Controller mainController = Controller(E_CONTROLLER_MASTER);

	goDistancePID(1);



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
