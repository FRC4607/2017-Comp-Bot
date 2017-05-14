#include "GearEject.h"

GearEject::GearEject() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void GearEject::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void GearEject::Execute() {
	RobotMap::gearIntake->Set(-.5);
	RobotMap::gearIsInXDDD->Set(false);
	RobotMap::gearIsNotInXDDD->Set(true);
}

// Make this return true when this Command no longer needs to run execute()
bool GearEject::IsFinished() {

	if (Robot::oi->getCaptain()->GetRawButton(5)) {		// Pressing button 5 will kill the intake while eject is running
			return true;
		}

			else {
				return false;
		}
}

// Called once after isFinished returns true
void GearEject::End() {
	RobotMap::gearIntake->Set(0);

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void GearEject::Interrupted() {

}
