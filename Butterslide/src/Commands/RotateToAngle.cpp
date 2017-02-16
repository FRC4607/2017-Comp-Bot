#include "RotateToAngle.h"

RotateToAngle::RotateToAngle(double boat) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	this->setpoint=boat;
	Requires(Robot::drivetrain.get());
}

// Called just before this Command runs the first time
void RotateToAngle::Initialize() {
	Robot::drivetrain->SetSetpoint(RobotMap::drivetrainAHRS->GetAngle() + setpoint);
	Robot::drivetrain->Enable();
}

// Called repeatedly when this Command is scheduled to run
void RotateToAngle::Execute() {
	double error = Robot::drivetrain->GetSetpoint() - RobotMap::drivetrainAHRS->GetAngle();
	double percentError = error/setpoint;
}

// Make this return true when this Command no longer needs to run execute()
bool RotateToAngle::IsFinished() {
	return Robot::drivetrain->OnTarget();
}

// Called once after isFinished returns true
void RotateToAngle::End() {
	Robot::drivetrain->Disable();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RotateToAngle::Interrupted() {
	End();
}
