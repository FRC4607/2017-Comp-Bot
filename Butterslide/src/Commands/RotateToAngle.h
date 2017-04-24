#ifndef RotateToAngle_H
#define RotateToAngle_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

class RotateToAngle : public Command {
public:
	double setpoint;

	//X offset from camera to center of shooter,
	//with camera to the left of the shooter resulting in +x value
	//in same units as vision X
	const double X_OFFSET = .5;

	//Z offset from camera to center of shooter,
	//with camera in front of the shooter resulting in +z value
	//in same units as vision Z and vision X
	const double Z_OFFSET =.5;
	bool wasTargetLock = false;
	RotateToAngle(double);
	RotateToAngle(double, bool);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // RotateToAngle_H
