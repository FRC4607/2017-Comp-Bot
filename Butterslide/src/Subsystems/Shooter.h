#ifndef Shooter_H
#define Shooter_H

#include <Commands/PIDSubsystem.h>
#include <CANTalon.h>
#include "WPILib.h"

class Shooter : public PIDSubsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	std::shared_ptr<CANTalon> gun;
	std::shared_ptr<Encoder> encoderRpg;
	std::shared_ptr<PIDController> pIDControllerShooter;

public:
	Shooter();

	void InitDefaultCommand();
	void ImaFireInMaleeba(float speed);
	double ReturnPIDInput();
	void UsePIDOutput(double output);
};

#endif  // Shooter_H
