#include "AllignWithPeg.h"

AllignWithPeg::AllignWithPeg() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::drivetrain.get());
}

// Called just before this Command runs the first time
void AllignWithPeg::Initialize() {

	Robot::drivetrain->Enable();
}

// Called repeatedly when this Command is scheduled to run
void AllignWithPeg::Execute() {

	Robot::drivetrain->AllignWithGearPeg();
}

// Make this return true when this Command no longer needs to run execute()
bool AllignWithPeg::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void AllignWithPeg::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AllignWithPeg::Interrupted() {

}
