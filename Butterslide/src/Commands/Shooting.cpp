#include "Shooting.h"

Shooting::Shooting() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void Shooting::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void Shooting::Execute() {
if(RobotMap::rpg1->Get() == 0){
	Robot::rpg->ImaFireInMaleeba(-.52);
}

else {
	Robot::rpg->ImaFireInMaleeba(0);
}
}

// Make this return true when this Command no longer needs to run execute()
bool Shooting::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void Shooting::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Shooting::Interrupted() {

}
