// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Driving.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

Driving::Driving(): Command() {
        // Use requires() here to declare subsystem dependencies
    Requires(Robot::drivetrain.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void Driving::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void Driving::Execute() {
	Robot::drivetrain->DrivingWithJoystick();

}

// Make this return true when this Command no longer needs to run execute()
bool Driving::IsFinished() {
    return false;
}

// Called once after isFinished returns true
void Driving::End() {
//	RobotMap::drivetrainFrontLeft->Set(0);
//	RobotMap::drivetrainFrontRight->Set(0);
//	RobotMap::drivetrainRearLeft->Set(0);
//	RobotMap::drivetrainRearRight->Set(0);
//	RobotMap::drivetrainFrontStrafe->Set(0);
//	RobotMap::drivetrainRearStrafe->Set(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Driving::Interrupted() {
	End();

}




