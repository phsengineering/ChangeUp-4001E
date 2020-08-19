#include "main.h"
#include "subsystems.hpp"
#include <stdio.h>

using namespace pros;

void turnAnglePID(double angle) {

		printf("\033[1;32m[PID TURN STARTING] - \033[0m");
		printf("\033[1;36mAttempting to Turn: \033[0m");
		printf(" %lf", angle);
		printf(" degrees\n");

		bool displayValues = true;
		bool driveMotors = true;

		driveLF.tare_position();
    driveRF.tare_position();
    driveLB.tare_position();
    driveRB.tare_position();

    double TARGET = driveLF.get_position() + angle;
    double HALFWAY = driveLF.get_position() + angle / 4;

    double currentValue = driveLF.get_position();
    double currentError = TARGET - currentValue;
    double previousError = 0;

    bool accel = true;

    double kP  =  10;
    double kI  =  0.000;
    double kD  =  0.000;

		double acceptableError = 0.05;

    double maxRate = 90;

    while(fabs(currentError) > acceptableError) {
        if(angle > 0 && currentValue > HALFWAY)
            accel = false;
        else if(angle < 0 && currentValue < HALFWAY)
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

				double changingCommand = 0;

				if (driveMotors == true) {
					if (fabs(command) < 1) {
						if (command > 0) {
							turnDrive(25);
						} else {
							turnDrive(-25);
						}
						pros::delay(20);
					} else{
						turnDrive(command*20);
						changingCommand = 0;
					}
				}

        pros::delay(5);

        if(accel) {
            if(maxRate < 120)
            maxRate += 10;
        }

        currentValue = driveLF.get_position();
        previousError = currentError;
        currentError = TARGET - currentValue;

				if (displayValues == true) {
					printf("currentError: %lf", currentError);
					printf("   command: %lf", command);
					printf("   position: %lf", currentValue);
					printf("   target: %lf\n", TARGET);
				}
    }

		printf("\033[1;32m[PID TURN COMPLETE] - \033[0m");
		printf("\033[1;33mThis PID Loop has hopefully turned: \033[0m");
		printf(" %lf", angle);
		printf(" degrees\n");
    driveLF.move_velocity(0);
    driveRF.move_velocity(0);
    driveLB.move_velocity(0);
    driveRB.move_velocity(0);
}
