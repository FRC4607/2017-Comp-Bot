#include "Feed.h"
#include "../Robot.h"

Feed::Feed() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void Feed::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void Feed::Execute() {
Robot::ammo->FeederBarSetSpeed(.05);

}

// Make this return true when this Command no longer needs to run execute()
bool Feed::IsFinished() {
	return Robot::oi->getDriver()->GetRawButton(4);
}

// Called once after isFinished returns true
void Feed::End() {
Robot::ammo->FeederBarSetSpeed(0);

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Feed::Interrupted() {
}

