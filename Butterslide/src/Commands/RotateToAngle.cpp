#include "RotateToAngle.h"
#include "math.h"

RotateToAngle::RotateToAngle(double boat) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	this->setpoint=boat;
	Robot::drivetrain->SetTargetLock(false);
	Requires(Robot::drivetrain.get());
}

RotateToAngle::RotateToAngle(double boat, bool targetLock) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	this->setpoint=boat;
	Robot::drivetrain->SetTargetLock(targetLock);
	Requires(Robot::drivetrain.get());
}


// Called just before this Command runs the first time
void RotateToAngle::Initialize() {

	if(Robot::drivetrain->GetTargetLock()){


		double totalX, totalZ;

		totalX = Robot::visionCheck->HighGoalPosX() + X_OFFSET;
		totalZ = Robot::visionCheck->HighGoalDistance() + Z_OFFSET;

		//Calculate correct angle based off offsets and convert to degrees
		setpoint = atan(totalX/totalZ)/ 3.14159 *180;
		wasTargetLock = true;
		Robot::drivetrain->drivetrainPIDRunning = true;
	}



	Robot::drivetrain->SetSetpoint(RobotMap::drivetrainAHRS->GetAngle() + setpoint);
	Robot::drivetrain->Enable();
}

// Called repeatedly when this Command is scheduled to run
void RotateToAngle::Execute() {
	float percentError;
	double error;
	double currentAngle;

	if(Robot::drivetrain->GetTargetLock()){

		double totalX, totalZ;

		totalX = Robot::visionCheck->HighGoalPosX() + X_OFFSET;
		totalZ = Robot::visionCheck->HighGoalDistance() + Z_OFFSET;

		//Calculate correct angle based off offsets and convert to degrees
		setpoint = atan(totalX/totalZ)/ 3.14159 *180;
		Robot::drivetrain->SetSetpoint(RobotMap::drivetrainAHRS->GetAngle() + setpoint);
	}

	currentAngle = RobotMap::drivetrainAHRS->GetAngle();
	error = setpoint - currentAngle;
	percentError = error / setpoint;

	SmartDashboard::PutNumber( "Percent Error", percentError);
	SmartDashboard::PutNumber( "Absolute Error", error);
}

// Make this return true when this Command no longer needs to run execute()
bool RotateToAngle::IsFinished() {
	if(!Robot::drivetrain->GetTargetLock()){
		return wasTargetLock ||Robot::drivetrain->OnTarget();
	}
	return false;
}

// Called once after isFinished returns true
void RotateToAngle::End() {
	Robot::drivetrain->SetTargetLock(false);
	Robot::drivetrain->Disable();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RotateToAngle::Interrupted() {
	if(!Robot::drivetrain->GetTargetLock()){
		End();
	}
}
