#ifndef RotateToAngle_H
#define RotateToAngle_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

class RotateToAngle : public Command {
public:
	double setpoint;

	RotateToAngle(double);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // RotateToAngle_H
