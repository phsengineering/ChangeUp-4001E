#include "main.h"
#include "subsystems.hpp"
#include <stdio.h>

using namespace pros;

void trackTurn(double degreeInput) {

  pros::ADIEncoder leftEncoder ('E', 'F', false);
  pros::ADIEncoder rightEncoder ('C', 'D', false);
  pros::ADIEncoder middleEncoder ('A', 'B', true);

  double LEFTENCODER, RIGHTENCODER, MIDDLEENCODER;

  double PI = 3.14159265;

  double diameterOfTrack = 2.75; //inches
  double circumference = 2*PI*(diameterOfTrack/2);

  double sl = 13.875 / 2;
  double sr = 13.875 / 2;
  double ss = 5.75;

  double theta, rr, dly, dlx;

		bool displayValues = true;
		bool driveMotors = true;

    double TARGET = (theta * (180/PI)) + degreeInput;

    double currentValue = (theta * (180/PI));
    double currentError = TARGET - currentValue;
    double previousError = 0;

    bool accel = true;

    double kP  =  6;  //100
    double kI  =  0;
    double kD  =  1; //20

		double acceptableError = 0.0; // how close the encoder values have to be to the desired amount to stop the while loop
		double maxNumberOfCorrections = 50; // max number of small corrections allowed to make at the end of turn

		double correctionAmount = 0;
    double maxRate = 90;

		double commandOffset = 750;
		double commandMax = 40;
		double commandSmallCorrection = 8;

    double acceptableCount = 0;
    double acceptableAmount = 100;

    double commandCount = 0;

    while(fabs(currentError) > acceptableError && acceptableCount < acceptableAmount) {

      if (fabs(currentError) < acceptableError) {
        acceptableCount++;
      }

      LEFTENCODER = leftEncoder.get_value();
      RIGHTENCODER = rightEncoder.get_value();
      MIDDLEENCODER = middleEncoder.get_value();

      double leftCorrection = (LEFTENCODER / 360) * circumference;
      double rightCorrection = (RIGHTENCODER / 360) * circumference;
      double middleCorrection = (MIDDLEENCODER / 360) * circumference;

      theta = ((leftCorrection - rightCorrection) / (sl + sr));

        double p  = kP * currentError;
        double i  = kI;
        double d  = kD * (currentError - previousError);

        double command = p + i + d;

				if (driveMotors == true) {
            xDriveStrafe(0,0,command);
				}

        if (command < 6.5) {
          commandCount++;
          if (commandCount >= 150) {
            break;
          }
        }

        pros::delay(10);

        currentValue = (theta * (180/PI));
        previousError = currentError;
        currentError = TARGET - currentValue;

				if (displayValues == true) {
					printf("currentError: %lf", currentError);
					printf("   command: %lf", command);
					printf("   position: %lf", currentValue);
					printf("   acceptableCount: %lf\n", acceptableCount);
				}
    }
    acceptableCount = 0;
		correctionAmount = 0;
		printf("\033[1;32m[PID TURN COMPLETE] - \033[0m");
		printf("\033[1;33mThis PID Loop has hopefully turned: \033[0m");
		printf(" %lf", degreeInput);
		printf(" degrees\n");
    driveLF.move_velocity(0);
    driveRF.move_velocity(0);
    driveLB.move_velocity(0);
    driveRB.move_velocity(0);
}
