void goDistancePID(double inches) {

		double distance = (0.563 + inches) / 5.93;

		driveLF.tare_position();
    driveRF.tare_position();
    driveLB.tare_position();
    driveRB.tare_position();

    double TARGET = driveLF.get_position() + distance;
    double HALFWAY = driveLF.get_position() + distance / 4;

    double currentValue = driveLF.get_position();
    double currentError = TARGET - currentValue;
    double previousError = 0;

		printf("Current Value: %lf\n", currentValue);
		printf("Current Error: %lf\n", currentError);

    bool accel = true;

    double kP  =  2;
    double kI  =  0.000;
    double kD  =  15.000;

		double acceptableError = 0.05;

    double maxRate = 90;

    while(fabs(currentError) > acceptableError) {
			printf("currentError: %lf", currentError);
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
				printf("   command: %lf", command);

				if (fabs(command) < 1) {

					if (command > 0) {
						drive(22,0);
					} else {
						drive(-22,0);
					}
					pros::delay(20);
				} else{
					drive(command*20, 0);
				}

        pros::delay(20);

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
