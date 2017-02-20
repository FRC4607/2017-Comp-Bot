#include "Intake.h"
#include "../RobotMap.h"

Intake::Intake() : Subsystem("Intake") {
	loader = RobotMap::ammoElevator;
	sucker = RobotMap::ammoIntake;
	climber = RobotMap::ropeMonster;
}

void Intake::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Intake::ElevatorSpeed(float speed){
	loader->Set(speed);
}

void Intake::FloorIntakeSpeed(float speed){
	sucker->Set(speed);
}

void Intake::ClimberSpeed(float speed){
	climber->Set(speed);
}
