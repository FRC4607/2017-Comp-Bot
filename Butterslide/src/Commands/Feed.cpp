#include "Feed.h"
#include "../Robot.h"

Feed::Feed(double speed) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	this->speed = speed;
}
Feed::Feed(){
	speed = -2;
}

// Called just before this Command runs the first time
void Feed::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void Feed::Execute() {
	if(speed == -2){
		if(RobotMap::ammoIntake->Get() == 0){
			Robot::ammo->FloorIntakeSpeed(-.50);
		}

		else{
			Robot::ammo->FloorIntakeSpeed(0);
		}
	}
	else {
		Robot::ammo->FloorIntakeSpeed(speed);
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

