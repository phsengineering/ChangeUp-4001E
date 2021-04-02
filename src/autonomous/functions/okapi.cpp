#include "main.h"
#include "subsystems.hpp"
#include "okapi/api.hpp"

using namespace okapi;

std::shared_ptr<okapi::OdomChassisController> chassis = ChassisControllerBuilder()
      .withMotors(
          {4, 5}, // Left motors are 1 & 2 (reversed)
          {8, 9}    // Right motors are 3 & 4
        )
      //  .withMaxVoltage(2000)
        .withMaxVelocity(275)
        .withGains(
          { 0.00345, 0.00000, 0.00009 }, // Distance controller gains
           { 0.01345, 0.000, 0.0022 }, // Turn controller gains
           { 0.0000, 0.0000, 0.00000 }  // Angle controller gains
        )

        .withSensors(
          okapi::ADIEncoder{'D', 'C', true}, // left encoder in ADI ports A & B
          okapi::ADIEncoder{'G', 'H', false},  // right encoder in ADI ports C & D (reversed)
          okapi::ADIEncoder{'A', 'B', false}  // middle encoder in ADI ports E & F
        )
        //{wheel diameter, wheel track, length to middle wheel, middle wheel diameter}.
        .withDimensions(AbstractMotor::gearset::blue, {{2.75_in, 7_in, 4_in, 2.75_in}, quadEncoderTPR})
        .withOdometry()
        .buildOdometry();



std::shared_ptr<AsyncMotionProfileController> profileController =
  AsyncMotionProfileControllerBuilder()
    .withLimits({
      3, // Maximum linear velocity of the Chassis in m/s
      6.0, // Maximum linear acceleration of the Chassis in m/s/s
      10.0 // Maximum linear jerk of the Chassis in m/s/s/s
    })
    .withOutput(chassis)
    .buildMotionProfileController();

void okapiDrive() {
  chassis->turnAngle(-90_deg);
}

void okapiPath() {
  chassis->driveToPoint({3_ft, 3_ft});
/*  profileController->generatePath({
    {0_ft, 0_ft, 0_deg},
    {4_ft, -5_ft, 0_deg},
  }, "A" );
  profileController->setTarget("A");
  profileController->waitUntilSettled(); */
}
