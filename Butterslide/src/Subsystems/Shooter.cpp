#include "Shooter.h"
#include "../RobotMap.h"
#include "SmartDashboard/SmartDashboard.h"
#include "LiveWindow/LiveWindow.h"
#include "../Commands/ShootSetPoint.h"

Shooter::Shooter() : PIDSubsystem("Shooter", 1.0, 0.0, 0.0, 0.0) {
	gun = RobotMap::rpg1;
    SetAbsoluteTolerance(0.2);
    GetPIDController()->SetContinuous(true);
	encoderRpg = RobotMap::shooterEncoderRpg;
	pIDControllerShooter = RobotMap::shooterPIDController;
	gun->SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
	gun->SetAllowableClosedLoopErr(0);
	gun->SelectProfileSlot(0);
	gun->SetF(0.0);
	gun->SetP(0.1);
	gun->SetI(0.0);
	gun->SetD(0.0);
}

void Shooter::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
	// SetDefaultCommand(new ShootSetPoint(-500));
}

double Shooter::ReturnPIDInput() {
	return encoderRpg->GetRate();

}

void Shooter::UsePIDOutput(double output) {
	 gun->Set(output);
}

void Shooter::ImaFireInMaleeba(float speed){
	gun->Set(speed);
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
