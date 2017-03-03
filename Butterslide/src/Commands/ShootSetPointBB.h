#ifndef ShootSetPointBB_H
#define ShootSetPointBB_H

#include "../Robot.h"
#include "Commands/Subsystem.h"

class ShootSetPointBB : public Command {
public:
	double setpoint;
	ShootSetPointBB(double);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // ShootSetPoint_H
