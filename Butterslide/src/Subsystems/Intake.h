#ifndef Intake_H
#define Intake_H

#include <Commands/Subsystem.h>
#include <CANTalon.h>

class Intake : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

public:
	Intake();
	std::shared_ptr<CANTalon> loader;
	std::shared_ptr<CANTalon> sucker;
	void InitDefaultCommand();
	void FeederBarSetSpeed(float);
	void FloorIntakeSpeed(float);
};

#endif  // Intake_H
