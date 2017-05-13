#include "GearIntake.h"

GearIntake::GearIntake() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void GearIntake::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void GearIntake::Execute() {
	RobotMap::gearIntake->Set(-.5);
}

// Make this return true when this Command no longer needs to run execute()
bool GearIntake::IsFinished() {
	if (RobotMap::gearIntake->GetReverseLimitOK() == false) {
		RobotMap::gearIsInXDDD->Set(true);
		return true;
	}

		else {
			RobotMap::gearIsNotInXDDD->Set(true);
			return false;
	}
}

// Called once after isFinished returns true
void GearIntake::End() {
	RobotMap::gearIntake->Set(0);

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void GearIntake::Interrupted() {

}
