#include "main.h"
#include "subsystems.hpp"
#include <stdio.h>

using namespace pros;

pros::ADIEncoder middleEncoder ('C', 'D', true);
pros::ADIEncoder leftEncoder ('A', 'B', false);
pros::ADIEncoder rightEncoder ('E', 'F', true);

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

		double encoderStart = middleEncoder.get_value();
		double leftEncoderStart = leftEncoder.get_value();
		double rightEncoderStart = rightEncoder.get_value();

		double lefts = (driveLF.get_position() + driveLB.get_position()) / 2;
		double rights = (driveRF.get_position() + driveRB.get_position()) / 2;

		double alls = (lefts + rights) / 2;

    double TARGET = driveLB.get_position() + distance;
    double HALFWAY = driveLB.get_position() + distance / 4;

    double currentValue = driveLB.get_position();
    double currentError = TARGET - currentValue;
    double previousError = 0;

    double kP  =  2.2;
    double kI  =  0;
    double kD  =  12.000;

		double acceptableError = 0.02;
		double speedCorrection = 1;

		double countOscilations = 0;

		double timer = 0;


    while(fabs(currentError) > acceptableError || fabs(previousError) > acceptableError) {

        double p  = kP * currentError;
        double i  = kI;
        double d  = kD * (currentError - previousError);

        double command = p + i + d;

				if (driveMotors == true) {
					if (fabs(command) < 1) {
						if (command > 0) {
							//autonDrive(18, speed);
								autonDriveVary(18/10, 18, speed); // if they are the same if this ever even happens
						} else {
							//autonDrive(-18, speed);
								autonDriveVary(-18/10, -18, speed); // if they are the same if this ever even happens
						}
					} else{
							double realCommand = command * 15 * speedCorrection;
							printf("\033[1;32m22222222222222 - \n\033[0m");
							autonDriveVary(realCommand*10, realCommand, speed); // if they are the same if this ever even happens
						}
					}


				lefts = (driveLF.get_position() + driveLB.get_position()) / 2;
				rights = (driveRF.get_position() + driveRB.get_position()) / 2;
				alls = (lefts + rights) / 2;

				double test = middleEncoder.get_value() - encoderStart;
				double leftEncoderPos = leftEncoder.get_value();
				double rightEncoderPos = rightEncoder.get_value();

        currentValue = alls;
        previousError = currentError;
        currentError = TARGET - currentValue;
				if (displayValues == true) {
					printf("%lf", timer);
					printf(",%lf", lefts);
					printf(",%lf\n", rights);
					delay(10);
				}

				timer++;

    }
		printf("\033[1;32m[PID DRIVE COMPLETE] - \033[0m");
		printf("\033[1;33mThis PID Loop has hopefully gone: \033[0m");
		printf(" %lf", inches);
		printf(" inches\n");
		stopAllDrive();
		timer = 0;
}
