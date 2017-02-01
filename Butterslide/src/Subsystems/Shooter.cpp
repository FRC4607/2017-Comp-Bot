#include "Shooter.h"
#include "../RobotMap.h"
#include "SmartDashboard/SmartDashboard.h"
#include "LiveWindow/LiveWindow.h"
#include "../Commands/ShootSetPoint.h"

Shooter::Shooter() : PIDSubsystem("Shooter", 1.0, 0.0, 0.0, 0.0) {
	gun = RobotMap::rpg1;
    SetAbsoluteTolerance(0.2);
    GetPIDController()->SetContinuous(true);
    LiveWindow::GetInstance()->AddActuator("Shooter", "PIDSubsystem Controller", GetPIDController());
	gun = RobotMap::rpg1;
	encoderRpg = RobotMap::shooterEncoderRpg;
	pIDControllerShooter = RobotMap::shooterPIDController;
}

void Shooter::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
	SetDefaultCommand(new ShootSetPoint(-500));
}

double Shooter::ReturnPIDInput() {
	return encoderRpg->GetRate();

}

void Shooter::UsePIDOutput(double output) {
	 gun->PIDWrite(output);
}

void Shooter::ImaFireInMaleeba(float speed){
	gun->Set(speed);
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
