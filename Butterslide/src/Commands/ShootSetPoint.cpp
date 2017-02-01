#include "ShootSetPoint.h"

ShootSetPoint::ShootSetPoint(double setpoint) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	this->setpoint=setpoint;
}

// Called just before this Command runs the first time
void ShootSetPoint::Initialize() {
	Robot::rpg->SetSetpoint(setpoint);
	Robot::rpg->Enable();
}

// Called repeatedly when this Command is scheduled to run
void ShootSetPoint::Execute() {
	SmartDashboard::PutNumber("Encoder Rate", RobotMap::shooterEncoderRpg->GetRate());

}

// Make this return true when this Command no longer needs to run execute()
bool ShootSetPoint::IsFinished() {
	return Robot::rpg->OnTarget();

}

// Called once after isFinished returns true
void ShootSetPoint::End() {
	Robot::rpg->Disable();

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShootSetPoint::Interrupted() {

}
