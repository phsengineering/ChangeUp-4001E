#include "main.h"
#include "subsystems.hpp"
#include <stdio.h>

using namespace pros;

void goDistancePID(double inches, double speed) {

		printf("\033[1;32m[PID DRIVE STARTING] - \033[0m");
		printf("\033[1;36mAttempting to Go: \033[0m");
		printf(" %lf", inches);
		printf(" inches\n");

		bool displayValues = true;
		bool driveMotors = true;

		double distance2 = (0.25 + inches) / 1.03;
		double distance = (-0.125 + distance2) / 5.89;

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

    double kP  =  2.5;
    double kI  =  0;
    double kD  =  12.000;

		double acceptableError = 0.02;
		double speedCorrection = 1;

    double maxRate = 35;

		double countOscilations = 0;

		double timer = 0;


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
							autonDrive(18, speed);
						} else {
							autonDrive(-18, speed);
						}
					} else{
						autonDrive(command*15*speedCorrection, speed);
					}
				}

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
/*
					printf("Current Error: %lf", currentError);
					printf("   Motor Command: %lf", command);
					printf("   Position: %lf", currentValue);
					printf("   Target: %lf\n", TARGET);
*/
					 // for .csv file
					printf("%lf", timer);
					//printf(",%lf", currentError);
					//printf(",%lf", command);
					printf(",%lf\n", currentValue);
					delay(10);
					//printf(",%lf\n", TARGET);

				}
				timer++;


    }
		printf("\033[1;32m[PID DRIVE COMPLETE] - \033[0m");
		printf("\033[1;33mThis PID Loop has hopefully gone: \033[0m");
		printf(" %lf", inches);
		printf(" inches\n");
    driveLF.move_velocity(0);
    driveRF.move_velocity(0);
    driveLB.move_velocity(0);
    driveRB.move_velocity(0);
		timer = 0;
}
