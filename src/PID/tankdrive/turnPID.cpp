#include "main.h"
#include "subsystems.hpp"
#include <stdio.h>

using namespace pros;

void turnAnglePID(double degreeInput) {

		printf("\033[1;32m[PID TURN STARTING] - \033[0m");
		printf("\033[1;36mAttempting to Turn: \033[0m");
		printf(" %lf", degreeInput);
		printf(" degrees\n");

		double angle = degreeInput*0.014 + 0.02;

		bool displayValues = true;
		bool driveMotors = true;

		driveLF.tare_position();
    driveRF.tare_position();
    driveLB.tare_position();
    driveRB.tare_position();

    double TARGET = ((fabs(driveLF.get_position()) + fabs(driveRF.get_position())) / 2) + angle;
    double HALFWAY = ((fabs(driveLF.get_position()) + fabs(driveRF.get_position())) / 2) + angle / 4;

    double currentValue = (fabs(driveLF.get_position()) + fabs(driveRF.get_position())) / 2;
    double currentError = TARGET - currentValue;
    double previousError = 0;

    bool accel = true;

    double kP  =  0.085;  //100
    double kI  =  0.0004;
    double kD  =  0.0000; //20

		double acceptableError = 0.001; // how close the encoder values have to be to the desired amount to stop the while loop
		double maxNumberOfCorrections = 20; // max number of small corrections allowed to make at the end of turn

		double correctionAmount = 0;
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
						if (fabs(command) < 0.001) {
							if (correctionAmount < maxNumberOfCorrections) {
								if (command > 0) {
									turnDrive(30);
								} else {
									turnDrive(-30);
								}
								pros::delay(10);
						  	correctionAmount++;
							} else {
								break;
							}
						} else{
							turnDrive(command*10000);
						changingCommand = 0;
						}
				}

        pros::delay(5);

        if(accel) {
            if(maxRate < 120)
            maxRate += 10;
        }

        currentValue = (fabs(driveLF.get_position()) + fabs(driveRF.get_position())) / 2;
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


































void curveTurn(double degreeInput) {

while(true) {
	double leftCurrent = driveLF.get_position();
	double rightCurrent = driveRF.get_position();

//	mainController.set_text(0, 0, "hello");

	printf("left: %lf", leftCurrent);
	printf("   right: %lf\n", rightCurrent);

	delay(100);
}



}
