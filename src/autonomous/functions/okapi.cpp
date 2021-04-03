#include "main.h"
#include "subsystems.hpp"
#include "okapi/api.hpp"

using namespace okapi;
/*
std::shared_ptr<okapi::OdomChassisController> chassis = ChassisControllerBuilder()
      .withMotors(
          {4, 5}, // Left motors are 1 & 2 (reversed)
          {8, 9}    // Right motors are 3 & 4
        )

        .withGains(
          { 0.00345, 0.00002, 0.00009 }, // Distance controller gains
          { 0.0, 0.0, 0.0 }, // Turn controller gains
          { 0.00022, 0.0001, 0.00003 }  // Angle controller gains
        )

        .withSensors(
          okapi::ADIEncoder{'D', 'C', true}, // left encoder in ADI ports A & B
          okapi::ADIEncoder{'G', 'H', false},  // right encoder in ADI ports C & D (reversed)
          okapi::ADIEncoder{'A', 'B', true}  // middle encoder in ADI ports E & F
        )
        //{wheel diameter, wheel track, length to middle wheel, middle wheel diameter}.
        .withDimensions(AbstractMotor::gearset::green, {{2.75_in, 7_in, 4_in, 2.75_in}, quadEncoderTPR})
        .withOdometry()
        .buildOdometry();

void okapiMove(double distance) {
  chassis->moveDistance(2_ft);
}
*/
