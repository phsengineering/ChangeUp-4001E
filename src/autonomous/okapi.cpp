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
        .withMaxVoltage(8000)
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

std::shared_ptr<AsyncMotionProfileController> profileController =
  AsyncMotionProfileControllerBuilder()
    .withLimits({
      1.0, // Maximum linear velocity of the Chassis in m/s
      2.0, // Maximum linear acceleration of the Chassis in m/s/s
      10.0 // Maximum linear jerk of the Chassis in m/s/s/s
    })
    .withOutput(chassis)
    .buildMotionProfileController();

void okapiDrive() {
  chassis->setState({0_in, 0_in, 0_deg});
  chassis->driveToPoint({2_ft, 2_ft});
}

void okapiPath() {
  profileController->generatePath({
    {0_ft, 0_ft, 0_deg}, {2_ft, 2_ft, 0_deg}}, "A"
  );
  profileController->setTarget("A");
  profileController->waitUntilSettled();
}
