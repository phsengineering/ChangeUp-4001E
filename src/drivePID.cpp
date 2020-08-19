#include "main.h"
#include "subsystems.hpp"
#include <stdio.h>

using namespace pros;

void goDistancePID(double inches) {

		printf("\033[1;32m[PID DRIVE STARTING] - \033[0m");
		printf("\033[1;36mAttempting to Go: \033[0m");
		printf(" %lf", inches);
		printf(" inches\n");

		bool displayValues = true;
		bool driveMotors = true;

		double distance = (-0.1 + inches) / 5.89;

		driveLF.tare_position();
    driveRF.tare_position();
    driveLB.tare_position();
    driveRB.tare_position();

		double fronts = (driveLF.get_position() + driveRF.get_position()) / 2;
		double backs = (driveLB.get_position() + driveRB.get_position()) / 2;

		double alls = (fronts + backs) / 2;

    double TARGET = driveLB.get_position() + distance;
    double HALFWAY = driveLB.get_position() + distance / 4;

    double currentValue = driveLB.get_position();
    double currentError = TARGET - currentValue;
    double previousError = 0;

    bool accel = true;

    double kP  =  2;
    double kI  =  0.00;
    double kD  =  0.000;

		double acceptableError = 0.015;

    double maxRate = 50;


    while(fabs(currentError) > acceptableError || fabs(previousError) > acceptableError) {

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

				if (driveMotors == true) {
					if (fabs(command) < 1) {
						if (command > 0) {
							drive(12,0);
						} else {
							drive(-12,0);
						}
						pros::delay(20);
					} else{
						drive(command*15, 0);
					}
				}

        pros::delay(5);

        if(accel) {
            if(maxRate < 120)
            maxRate += 10;
        }

				fronts = (driveLF.get_position() + driveRF.get_position()) / 2;
				backs = (driveLB.get_position() + driveRB.get_position()) / 2;
				alls = (fronts + backs) / 2;

        currentValue = alls;
        previousError = currentError;
        currentError = TARGET - currentValue;
				if (displayValues == true) {
					printf("Current Error: %lf", currentError);
					printf("   Motor Command: %lf", command);
					printf("   Position: %lf", currentValue);
					printf("   Target: %lf\n", TARGET);
				}
    }
		printf("\033[1;32m[PID DRIVE COMPLETE] - \033[0m");
		printf("\033[1;33mThis PID Loop has hopefully gone: \033[0m");
		printf(" %lf", inches);
		printf(" inches\n");
    driveLF.move_velocity(0);
    driveRF.move_velocity(0);
    driveLB.move_velocity(0);
    driveRB.move_velocity(0);
}
