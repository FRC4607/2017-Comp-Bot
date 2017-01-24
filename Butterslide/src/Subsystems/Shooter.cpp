#include "Shooter.h"
#include "../RobotMap.h"

Shooter::Shooter() : Subsystem("Shooter") {

	gun = RobotMap::rpg1;
}

void Shooter::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

void Shooter::ImaFireInMaleeba(float speed){
	gun->Set(speed);

}
// Put methods for controlling this subsystem
// here. Call these from Commands.
