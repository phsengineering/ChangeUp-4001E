#include "main.h"
#include "subsystems.hpp"
#include <stdio.h>

using namespace pros;

void turnAnglePID(double angle) {

		driveLF.tare_position();
    driveRF.tare_position();
    driveLB.tare_position();
    driveRB.tare_position();

    double TARGET = driveLF.get_position() + angle;
    double HALFWAY = driveLF.get_position() + angle / 4;

    double currentValue = driveLF.get_position();
    double currentError = TARGET - currentValue;
    double previousError = 0;

		printf("Current Value: %lf\n", currentValue);
		printf("Current Error: %lf\n", currentError);

    bool accel = true;

    double kP  =  2;
    double kI  =  0.000;
    double kD  =  10.000;

		double acceptableError = 0.05;

    double maxRate = 90;

    while(fabs(currentError) > acceptableError) {
			printf("currentError: %lf", currentError);
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
				printf("   command: %lf", command);

				double changingCommand = 0;

				if (fabs(command) < 1) {
					changingCommand = 1;
					printf("   ChangingCommand?: %lf", changingCommand);

					if (command > 0) {
						turnDrive(15);
					} else {
						turnDrive(-15);
					}
					pros::delay(20);
				} else{
					turnDrive(command*20);
					changingCommand = 0;
					printf("   ChangingCommand?: %lf", changingCommand);
				}

        pros::delay(5);

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
