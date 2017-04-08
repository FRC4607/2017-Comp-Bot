#include "Climbing.h"
#include "../Robot.h"

Climbing::Climbing() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void Climbing::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void Climbing::Execute() {

	if(RobotMap::ropeMonster->Get() == 0){
			Robot::ammo->ClimberSpeed(-1);
		}

		else{
			Robot::ammo->ClimberSpeed(0);
		}

}

// Make this return true when this Command no longer needs to run execute()
bool Climbing::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void Climbing::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Climbing::Interrupted() {

}
