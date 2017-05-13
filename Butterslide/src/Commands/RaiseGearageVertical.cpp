#include "RaiseGearageVertical.h"

RaiseGearageVertical::RaiseGearageVertical() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void RaiseGearageVertical::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void RaiseGearageVertical::Execute() {

	RobotMap::gearLift->Set(.5);

}

// Make this return true when this Command no longer needs to run execute()
bool RaiseGearageVertical::IsFinished() {
	if (RobotMap::gearLift->GetForwardLimitOK() == true) {
		return true;
	}
	else{
		return false;
	}
}

// Called once after isFinished returns true
void RaiseGearageVertical::End() {
	RobotMap::gearLift->Set(0);

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RaiseGearageVertical::Interrupted() {

}
