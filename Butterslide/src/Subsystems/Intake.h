#ifndef Intake_H
#define Intake_H

#include <Commands/Subsystem.h>
#include <CANTalon.h>

class Intake : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	std::shared_ptr<CANTalon> loader;
	std::shared_ptr<CANTalon> sucker;
	std::shared_ptr<CANTalon> climber;

public:
	Intake();

	void InitDefaultCommand();
	void ElevatorSpeed(float);
	void FloorIntakeSpeed(float);
	void ClimberSpeed(float);
};

#endif  // Intake_H
