#include "Intake.h"
#include "../RobotMap.h"

Intake::Intake() : Subsystem("Intake") {
	loader = RobotMap::ammoLoader;
	sucker = RobotMap::ammoIntake;
}

void Intake::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Intake::FeederBarSetSpeed(float speed){
	loader->Set(speed);
}

void Intake::FloorIntakeSpeed(float speed){
	sucker->Set(speed);
}
