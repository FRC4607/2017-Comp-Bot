#include "PunchOut.h"

PunchOut::PunchOut() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void PunchOut::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void PunchOut::Execute() {
	RobotMap::leftGearServo->Set(1);
	RobotMap::rightGearServo->Set(1);

}

// Make this return true when this Command no longer needs to run execute()
bool PunchOut::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void PunchOut::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PunchOut::Interrupted() {

}
