#include "main.h"
#include "subsystems.hpp"
#include <stdio.h>

using namespace pros;


void xDriveTurn(double degreeInput) {

		driveLF.tare_position();
		driveRF.tare_position();
		driveLB.tare_position();
		driveRB.tare_position();

		printf("\033[1;32m[PID TURN STARTING] - \033[0m");
		printf("\033[1;36mAttempting to Turn: \033[0m");
		printf(" %lf", degreeInput);
		printf(" degrees\n");

		double angle;

		if (degreeInput >= 0) {
			angle = (degreeInput * 0.987) - 2;
		} else {
			angle = (degreeInput * 1.03) - 1.23; // down is less turn, up is more
		}

		bool displayValues = true;
		bool driveMotors = true;

    double TARGET = (thatIMU.get_rotation()) + angle;

    double currentValue = thatIMU.get_rotation();
    double currentError = TARGET - currentValue;
    double previousError = 0;

    bool accel = true;

    double kP  =  0.01;  //100
    double kI  =  0.000;
    double kD  =  0.01; //20

		double acceptableError = 0.01; // how close the encoder values have to be to the desired amount to stop the while loop
		double maxNumberOfCorrections = 50; // max number of small corrections allowed to make at the end of turn

		double correctionAmount = 0;
    double maxRate = 90;

		double commandOffset = 700;
		double commandMax = 65;
		double commandSmallCorrection = 30;

    while(fabs(currentError) > acceptableError) {

        double p  = kP * currentError;
        double i  = kI;
        double d  = kD * (currentError - previousError);

        double command = p + i + d;

				if (driveMotors == true) {
						if (fabs(command) < 0.01) {
							if (correctionAmount < maxNumberOfCorrections) {
								if (command > 0) {
									autonTurn(commandSmallCorrection);
								} else {
									autonTurn(-commandSmallCorrection);
								}
						  	correctionAmount++;
							} else {
                break;
							}
              printf("\033[1;31m[SMALL CORRECTION] \033[0m");
						} else{
                if (command < 0) {
                  if (fabs(command*commandOffset) > commandMax) {
                    autonTurn(-commandMax);
                  } else {
                      autonTurn(command*commandOffset);
                  }
                } else {
                  if (command*commandOffset > commandMax) {
                    autonTurn(commandMax);
                  } else {
                    autonTurn(command*commandOffset);
                  }
             }
						}
				}

        pros::delay(10);

        if(accel) {
            if(maxRate < 120)
            maxRate += 10;
        }

        currentValue = thatIMU.get_rotation();
        previousError = currentError;
        currentError = TARGET - currentValue;

				if (displayValues == true) {
					printf("currentError: %lf", currentError);
					printf("   command: %lf", command);
					printf("   position: %lf", currentValue);
					printf("   target: %lf\n", TARGET);
				}
    }
		correctionAmount = 0;
		printf("\033[1;32m[PID TURN COMPLETE] - \033[0m");
		printf("\033[1;33mThis PID Loop has hopefully turned: \033[0m");
		printf(" %lf", angle);
		printf(" degrees\n");
    driveLF.move_velocity(0);
    driveRF.move_velocity(0);
    driveLB.move_velocity(0);
    driveRB.move_velocity(0);
}
