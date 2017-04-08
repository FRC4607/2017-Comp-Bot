#include "Feed.h"
#include "../Robot.h"

Feed::Feed(double speed) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	this->speed = speed;
}

// Called just before this Command runs the first time
void Feed::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void Feed::Execute() {
	if(RobotMap::ammoIntake->Get() == 0){
		Robot::ammo->FloorIntakeSpeed(speed);
	}

	else{
		Robot::ammo->FloorIntakeSpeed(0);
	}

}

// Make this return true when this Command no longer needs to run execute()
bool Feed::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void Feed::End() {


}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Feed::Interrupted() {
}

