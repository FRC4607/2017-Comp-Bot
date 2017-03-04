#include "ShootSetPoint.h"

ShootSetPoint::ShootSetPoint(double setpoint) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	this->setpoint=setpoint;
}

// Called just before this Command runs the first time
void ShootSetPoint::Initialize() {
/*	Robot::rpg->SetSetpoint(setpoint);
	Robot::rpg->Enable();
*/
	RobotMap::rpg1->SetControlMode(CANSpeedController::kSpeed);
	//Sets PIDF terms, in that order f = feedforward.
	//Feedforward of .1 is conservative and allows getting up to speed faster
	//but p value then is smaller resulting in slow response time
	RobotMap::rpg1->SetPID(.1,0,0,0.1);
	RobotMap::rpg1->Set(setpoint);
}

// Called repeatedly when this Command is scheduled to run
void ShootSetPoint::Execute() {
	SmartDashboard::PutNumber("Shooter SRX Error:", RobotMap::rpg1->GetClosedLoopError());

}

// Make this return true when this Command no longer needs to run execute()
bool ShootSetPoint::IsFinished() {
	//return Robot::rpg->OnTarget();
	return RobotMap::rpg1->GetClosedLoopError() == 0;
}

// Called once after isFinished returns true
void ShootSetPoint::End() {
	//Robot::rpg->Disable();
	RobotMap::rpg1->SetControlMode(CANSpeedController::kPercentVbus);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShootSetPoint::Interrupted() {
	End();
}
