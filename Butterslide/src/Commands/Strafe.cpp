#include "Strafe.h"

Strafe::Strafe(double speed, double time) {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  this->speed = speed;
  this->time = time;
}

// Called just before this Command runs the first time
void Strafe::Initialize() {
	SetTimeout(this->time);
}

// Called repeatedly when this Command is scheduled to run
void Strafe::Execute() {
  RobotMap::drivetrainFrontStrafe->Set(-speed);
  RobotMap::drivetrainRearStrafe->Set(speed);

}

// Make this return true when this Command no longer needs to run execute()
bool Strafe::IsFinished() {
	return IsTimedOut();
}

// Called once after isFinished returns true
void Strafe::End() {
	RobotMap::drivetrainFrontStrafe->Set(0);
	RobotMap::drivetrainRearStrafe->Set(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Strafe::Interrupted() {
  End();
}
