#ifndef ShootSetPoint_H
#define ShootSetPoint_H

#include "../Robot.h"
#include "Commands/Subsystem.h"

class ShootSetPoint : public Command {
public:
	double setpoint;
	ShootSetPoint(double);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // ShootSetPoint_H
