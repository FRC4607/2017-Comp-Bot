#ifndef Shooter_H
#define Shooter_H

#include <Commands/Subsystem.h>
#include <CANTalon.h>

class Shooter : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	std::shared_ptr<CANTalon> gun;


public:
	Shooter();

	void InitDefaultCommand();
	void ImaFireInMaleeba(float speed);
};

#endif  // Shooter_H
