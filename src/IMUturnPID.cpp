#include "main.h"
#include "subsystems.hpp"
#include <stdio.h>

using namespace pros;


void imuTurn(double degreeInput) {

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

    double TARGET = imu_sensor.get_rotation() + angle;
    double HALFWAY = imu_sensor.get_rotation() + angle / 4;

    double currentValue = imu_sensor.get_rotation();
    double currentError = TARGET - currentValue;
    double previousError = 0;

    bool accel = true;

    double kP  =  0.0022;  //100
    double kI  =  0.010;
    double kD  =  0.010; //20

		double acceptableError = 0.0005; // how close the encoder values have to be to the desired amount to stop the while loop
		double maxNumberOfCorrections = 50; // max number of small corrections allowed to make at the end of turn

		double correctionAmount = 0;
    double maxRate = 90;

    while(fabs(currentError) > acceptableError) {

        double p  = kP * currentError;
        double i  = kI;
        double d  = kD * (currentError - previousError);

        double command = p + i + d;

				if (driveMotors == true) {
						if (fabs(command) < 0.01) {
							if (correctionAmount < maxNumberOfCorrections) {
								if (command > 0) {
									turnDrive(5);
								} else {
									turnDrive(-5);
								}
								pros::delay(10);
						  	correctionAmount++;
							} else {
								break;
							}
						} else{
						turnDrive(command*1000);
						}
				}

        pros::delay(5);

        if(accel) {
            if(maxRate < 120)
            maxRate += 10;
        }

        currentValue = imu_sensor.get_rotation();
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
