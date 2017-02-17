#include "DrivetrainPID.h"
#include "RotateToAngle.h"

DrivetrainPID::DrivetrainPID(double rightSetpoint, double leftSetpoint, double strafeSetpoint, bool velocityControl, bool rotationalControl , double rotateOffset ) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	this->rightSetpoint = rightSetpoint;
	this->leftSetpoint = leftSetpoint;
	this->strafeSetpoint = strafeSetpoint;
	this->velocityControl = velocityControl;
	this->rotationalControl = rotationalControl;
	this->rotateOffset = rotateOffset;
	Requires(Robot::drivetrain.get());
}

// Called just before this Command runs the first time
void DrivetrainPID::Initialize() {
	if( velocityControl){
		RobotMap::drivetrainEncoderRearLeft->SetPIDSourceType( PIDSourceType::kRate);
		RobotMap::drivetrainEncoderRearRight->SetPIDSourceType( PIDSourceType::kRate);
		RobotMap::drivetrainEncoderRightStrafe->SetPIDSourceType( PIDSourceType::kRate);
	}
	else{
		RobotMap::drivetrainEncoderRearLeft->SetPIDSourceType( PIDSourceType::kDisplacement);
		RobotMap::drivetrainEncoderRearRight->SetPIDSourceType( PIDSourceType::kDisplacement);
		RobotMap::drivetrainEncoderRightStrafe->SetPIDSourceType( PIDSourceType::kDisplacement);
	}
	RobotMap::drivetrainLeftPIDController->SetSetpoint(leftSetpoint);
	RobotMap::drivetrainRightPIDController->SetSetpoint(rightSetpoint);
	RobotMap::drivetrainStrafePIDController->SetSetpoint(strafeSetpoint);

	RobotMap::drivetrainLeftPIDController->SetSetpoint(leftSetpoint);
	RobotMap::drivetrainRightPIDController->SetSetpoint(rightSetpoint);
	RobotMap::drivetrainStrafePIDController->SetSetpoint(strafeSetpoint);

	RobotMap::drivetrainFrontLeft->SetControlMode(frc::CANSpeedController::ControlMode::kFollower);
	RobotMap::drivetrainFrontRight->SetControlMode(frc::CANSpeedController::ControlMode::kFollower);
	RobotMap::drivetrainFrontStrafe->SetControlMode(frc::CANSpeedController::ControlMode::kFollower);

	RobotMap::drivetrainFrontLeft->Set(RobotMap::drivetrainRearLeft->GetDeviceID());
	RobotMap::drivetrainFrontRight->Set(RobotMap::drivetrainRearRight->GetDeviceID());
	RobotMap::drivetrainFrontStrafe->Set(RobotMap::drivetrainRearStrafe->GetDeviceID());

	if(rotationalControl){
		new RotateToAngle(rotateOffset);
	}
	RobotMap::drivetrainLeftPIDController->Enable();
	RobotMap::drivetrainRightPIDController->Enable();
	RobotMap::drivetrainStrafePIDController->Enable();



}

// Called repeatedly when this Command is scheduled to run
void DrivetrainPID::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool DrivetrainPID::IsFinished() {
	return RobotMap::drivetrainLeftPIDController->OnTarget() && RobotMap::drivetrainRightPIDController->OnTarget() && RobotMap::drivetrainStrafePIDController->OnTarget();
}

// Called once after isFinished returns true
void DrivetrainPID::End() {
	RobotMap::drivetrainLeftPIDController->Disable();
	RobotMap::drivetrainRightPIDController->Disable();
	RobotMap::drivetrainStrafePIDController->Disable();

	RobotMap::drivetrainFrontLeft->SetControlMode(frc::CANSpeedController::ControlMode::kPercentVbus);
	RobotMap::drivetrainFrontRight->SetControlMode(frc::CANSpeedController::ControlMode::kPercentVbus);
	RobotMap::drivetrainFrontStrafe->SetControlMode(frc::CANSpeedController::ControlMode::kPercentVbus);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DrivetrainPID::Interrupted() {
	End();
}
