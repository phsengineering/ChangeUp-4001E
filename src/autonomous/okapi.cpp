#include "api.h"
#include "main.h"
#include "subsystems.hpp"
#include "okapi/api.hpp"

using namespace okapi;

std::shared_ptr<OdomChassisController> chassis =
  ChassisControllerBuilder()
      .withMotors(
          {-4, -5}, // Left motors are 1 & 2 (reversed)
          {8, 9}    // Right motors are 3 & 4
        )
      //  .withDimensions(AbstractMotor::gearset::blue, {{2.75_in, 5_in, 4.3125_in, 2.75_in}, quadEncoderTPR}) //pass chassis dimensions. 2.75" tracking wheels, 4.25" distance and 4.375" b/w mid and middle wheel
        .withGains(
          {0.001, 0, 0.0000}, // distance controller gains
          {0.001, 0, 0.0000}, // turn controller gains
          {0.001, 0, 0.0000}  // angle controller gains (helps drive straight)
        )
        .withSensors(
          {'A', 'B'}, // left encoder in ADI ports A & B
          {'C', 'D', true},  // right encoder in ADI ports C & D (reversed)
          {'E', 'F'}  // middle encoder in ADI ports E & F
        )
          //{wheel diameter, wheel track, length to middle wheel, middle wheel diameter}.
        .withDimensions(AbstractMotor::gearset::blue, {{2.75_in, 7_in, 4_in, 2.75_in}, quadEncoderTPR})
        .withOdometry()
        .buildOdometry();


void okapiDrive() {
  chassis->setState({0_in, 0_in, 0_deg});
  chassis->driveToPoint({1_ft, 1_ft});
}
