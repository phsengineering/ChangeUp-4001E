#include "main.h"
#include "subsystems.hpp"
#include <stdio.h>

using namespace pros;


void turnTest(double degreeInput, double thatDelay) {

	leftEncoder.reset();
	rightEncoder.reset();
	middleEncoder.reset();

		printf("\033[1;32m[PID TURN STARTING] - \033[0m");
		printf("\033[1;36mAttempting to Turn: \033[0m");
		printf(" %lf", degreeInput);
		printf(" degrees\n");

		double angle;

		angle = degreeInput * 1;

		bool displayValues = true;
		bool driveMotors = true;

		double imu1 = thatIMU.get_rotation();
		double imu2 = thatIMU2.get_rotation();

    double TARGET = ((imu1 + imu2) / 2) + angle * 1.0170;

    double currentValue = thatIMU.get_rotation();
    double currentError = TARGET - currentValue;
    double previousError = 10;

    bool accel = true;

    double kP  =  18; //100
    double kI  =  0.0;
    double kD  =  85.0; //20

		/*    double kP  =  0.03; //100
		    double kI  =  0.0;
		    double kD  =  0.2; //20*/

		double acceptableError = 0.0; // how close the encoder values have to be to the desired amount to stop the while loop
		double maxNumberOfCorrections = 40; // max number of small corrections allowed to make at the end of turn 200

		double correctionAmount = 0;

		double commandOffset = 1;
		double commandMax = 100;
		double commandSmallCorrection = 17;

    while(fabs(currentError) > acceptableError) {

        double p  = kP * currentError;
        double i  = kI;
        double d  = kD * (currentError - previousError);

        double command = p + i + d;

				if (driveMotors == true) {
						if (fabs(command) < commandSmallCorrection) {
							if (correctionAmount < maxNumberOfCorrections) {
									autonTurn(command);
									correctionAmount++;
							} else {
                break;
							}
						} else{
                if (command < 0) {
                  if (fabs(command) > commandMax) {
                    autonTurn(-commandMax);
                  } else {
                      autonTurn(command);
                  }
                } else {
                  if (command > commandMax) {
                    autonTurn(commandMax);
                  } else {
                    autonTurn(command);
                  }
             }
						}
				}

        pros::delay(10);

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
/*		printf("\033[1;32m[PID TURN COMPLETE] - \033[0m");
		printf("\033[1;33mThis PID Loop has hopefully turned: \033[0m");
		printf(" %lf", angle);
		printf(" degrees\n"); */
    stopAllDrive();

		delay(thatDelay);
}
