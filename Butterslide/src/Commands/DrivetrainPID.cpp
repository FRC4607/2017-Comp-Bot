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

	//Set the encoders to return velocity if velocity control is desired
	if( velocityControl){
		RobotMap::drivetrainEncoderRearLeft->SetPIDSourceType( PIDSourceType::kRate);
		RobotMap::drivetrainEncoderRearRight->SetPIDSourceType( PIDSourceType::kRate);
		RobotMap::drivetrainEncoderRightStrafe->SetPIDSourceType( PIDSourceType::kRate);
	}
	//Set the encoders to return position if velocity control is not desired
	else{
		RobotMap::drivetrainEncoderRearLeft->SetPIDSourceType( PIDSourceType::kDisplacement);
		RobotMap::drivetrainEncoderRearRight->SetPIDSourceType( PIDSourceType::kDisplacement);
		RobotMap::drivetrainEncoderRightStrafe->SetPIDSourceType( PIDSourceType::kDisplacement);
	}

	//Set the setpoints of all the controllers
	RobotMap::drivetrainLeftPIDController->SetSetpoint(leftSetpoint);
	RobotMap::drivetrainRightPIDController->SetSetpoint(rightSetpoint);
	RobotMap::drivetrainStrafePIDController->SetSetpoint(strafeSetpoint);

	//Set the motors that go with talons being directly controlled to slave mode
	RobotMap::drivetrainFrontLeft->SetControlMode(frc::CANSpeedController::ControlMode::kFollower);
	RobotMap::drivetrainFrontRight->SetControlMode(frc::CANSpeedController::ControlMode::kFollower);
	RobotMap::drivetrainFrontStrafe->SetControlMode(frc::CANSpeedController::ControlMode::kFollower);

	//Set the motors with appropriate talon
	RobotMap::drivetrainFrontLeft->Set(RobotMap::drivetrainRearLeft->GetDeviceID());
	RobotMap::drivetrainFrontRight->Set(RobotMap::drivetrainRearRight->GetDeviceID());
	RobotMap::drivetrainFrontStrafe->Set(RobotMap::drivetrainRearStrafe->GetDeviceID());

	//If Rotational control is also being done, make a rotate to angle command and set the talons up for handling it
	/*if(rotationalControl){
		new RotateToAngle(rotateOffset);
		RobotMap::drivetrainRearLeft->rotatePID = true;
		RobotMap::drivetrainRearRight->rotatePID = true;
		RobotMap::drivetrainRearLeft->rotateAdjustment = 0;
		RobotMap::drivetrainRearRight->rotateAdjustment = 0;
	}
	else {
		RobotMap::drivetrainRearLeft->rotatePID = false;
		RobotMap::drivetrainRearRight->rotatePID = false;
	}*/

	//Enable PID
	RobotMap::drivetrainLeftPIDController->Enable();
	RobotMap::drivetrainRightPIDController->Enable();
	RobotMap::drivetrainStrafePIDController->Enable();



}

// Called repeatedly when this Command is scheduled to run
void DrivetrainPID::Execute() {

	//If rotational control is set the adjustments to the outputs of angular PID controller
	if(rotationalControl){
	//	RobotMap::drivetrainRearLeft->rotateAdjustment = Robot::drivetrain->leftSpeed;
	//	RobotMap::drivetrainRearRight->rotateAdjustment = Robot::drivetrain->rightSpeed;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool DrivetrainPID::IsFinished() {
	return RobotMap::drivetrainLeftPIDController->OnTarget() && RobotMap::drivetrainRightPIDController->OnTarget() && RobotMap::drivetrainStrafePIDController->OnTarget();
}

// Called once after isFinished returns true
void DrivetrainPID::End() {
	//Disable PID
	RobotMap::drivetrainLeftPIDController->Disable();
	RobotMap::drivetrainRightPIDController->Disable();
	RobotMap::drivetrainStrafePIDController->Disable();

	//Put the talons back to the usual control mode
	RobotMap::drivetrainFrontLeft->SetControlMode(frc::CANSpeedController::ControlMode::kPercentVbus);
	RobotMap::drivetrainFrontRight->SetControlMode(frc::CANSpeedController::ControlMode::kPercentVbus);
	RobotMap::drivetrainFrontStrafe->SetControlMode(frc::CANSpeedController::ControlMode::kPercentVbus);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DrivetrainPID::Interrupted() {
	End();
}
