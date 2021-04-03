#include "main.h"
#include "subsystems.hpp"
#include <stdio.h>
#include <math.h>

using namespace okapi;

std::shared_ptr<okapi::OdomChassisController> chassis = ChassisControllerBuilder()
      .withMotors(
          {4, 5}, // Left motors are 1 & 2 (reversed)
          {8, 9}    // Right motors are 3 & 4
        )

        .withGains(
          { 0.005, 0.005, 0.0012 }, // Distance controller gains
          { 0.0, 0.0, 0.0 } // Turn controller gains
        //  { 0.00022, 0.000, 0.00003 }  // Angle controller gains
        )

        /*
        .withGains(
          { 0.00345, 0.0, 0.0001 }, // Distance controller gains
          { 0.0, 0.0, 0.0 }, // Turn controller gains
          { 0.00022, 0.0001, 0.00003 }  // Angle controller gains
        )
        */
    //    .withClosedLoopControllerTimeUtil(50, 5, 1000_ms)
        .withMaxVelocity(350)

        .withSensors(
          okapi::ADIEncoder{'D', 'C', true}, // left encoder in ADI ports A & B
          okapi::ADIEncoder{'G', 'H', false},  // right encoder in ADI ports C & D (reversed)
          okapi::ADIEncoder{'A', 'B', true}  // middle encoder in ADI ports E & F
        )
        //{wheel diameter, wheel track, length to middle wheel, middle wheel diameter}.
        .withDimensions({AbstractMotor::gearset::blue, (5 / 3)}, {{2.75_in, 6.75_in, 4.5_in, 2.75_in}, quadEncoderTPR})
        .withOdometry()
        .buildOdometry();

void autonHandler() {
  std::cout << autons[current] << "\n";
  switch (current)
  {
      case 0: //  "Red Left [Corner/Side]",
          auton2balls(true);
          break;
      case 1: // "Red Left [Corner/Side/Middle]",
          auton3balls(true);
          break;
      case 2: // "Red Right [Corner/Side]",
          auton2balls(false);
          break;
      case 3: //  "Red Right [Corner/Side/Middle]",
          auton3balls(false);
          break;
      case 4: // "Red Just Score 1",
          flipout();
          break;
      case 5: // "Blue Left [Corner/Side]",
          auton2balls(true);
          break;
      case 6: // "Blue Left [Corner/Side/Middle]",
          auton3balls(true);
          break;
      case 7: // "Blue Right [Corner/Side]",
          auton2balls(false);
          break;
      case 8: //  "Blue Right [Corner/Side/Middle]",
          auton3balls(false);
          break;
      case 9: // "Blue Just Score 1",
          flipout();
          break;
      case 10: // "Prog Skills"
          skills();
          break;
  }
}

void auton2balls(bool left) {
  flipout();
  driveStraight(37.25, delayBetween); // drive to first ball on edge of tile

  intakeHandler(0);

  if (left == true) {
    turnTest(-76.75, delayBetween); // turn towards goal
  } else {
    turnTest(76.75, delayBetween); // turn towards goal
  }

  intakeHandler(-12000);
  driveFor(800, 75);
  intakeHandler(0);
  rollerHandler(-12000);
  delay(800);
  rollerHandler(0);
  driveStraight(-15, delayBetween+50); //back up from goal
}

void auton3balls(bool left) {

  delayBetween = 100;

  flipout();
  delay(500);
  driveStraight(36.25, delayBetween); // drive to first ball on edge of tile

  intakeHandler(0);

  if (left == true) {
    turnTest(-77.40, delayBetween); // turn towards goal
  } else {
    turnTest(77.40, delayBetween); // turn towards goal
  }

  intakeHandler(-12000);
  driveFor(900, 75);
  intakeHandler(0);
  rollerHandler(-12000);
  delay(800);
  rollerHandler(0);

  driveStraight(-36.75, delayBetween); //back up from goal

  if (left == true) {
    turnTest(135, delayBetween); // turn towards goal
  } else {
    turnTest(-135, delayBetween); // turn towards goal
  }

  intakeHandler(-9000);
  driveStraight(26.65, delayBetween);


  intakeHandler(0);
  driveStraight(-30, delayBetween);

  if (left == true) {
    turnTest(45, delayBetween); // turn towards goal
  } else {
    turnTest(-45, delayBetween); // turn towards goal
  }

  driveFor(900, 110);
  score();
  driveStraight(-20, 0);
}
