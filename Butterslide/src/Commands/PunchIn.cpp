#include "PunchIn.h"

PunchIn::PunchIn() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void PunchIn::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void PunchIn::Execute() {

	RobotMap::leftGearServo->Set(.6);
	RobotMap::rightGearServo->Set(.6);
}

// Make this return true when this Command no longer needs to run execute()
bool PunchIn::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void PunchIn::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PunchIn::Interrupted() {

}
