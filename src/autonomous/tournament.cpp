#include "main.h"
#include "subsystems.hpp"
#include <stdio.h>
#include <math.h>

using namespace pros;

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
  delay(500);
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
  /*flipout();
  delay(500);
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
  rollerHandler(0); */
  driveStraight(-37, delayBetween); //back up from goal

  if (left == true) {
    turnTest(135, delayBetween); // turn towards goal
  } else {
    turnTest(-135, delayBetween); // turn towards goal
  }

  intakeHandler(-8500);
  driveStraight(24.5, delayBetween);

  intakeHandler(0);
  driveStraight(-27.65, delayBetween);

  if (left == true) {
    turnTest(45, delayBetween); // turn towards goal
  } else {
    turnTest(-45, delayBetween); // turn towards goal
  }

  driveFor(1000, 110);

  score2();
}
