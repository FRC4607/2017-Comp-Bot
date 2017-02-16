#ifndef DrivetrainPID_H
#define DrivetrainPID_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

class DrivetrainPID : public Command {
public:
	double rightSetpoint, leftSetpoint, strafeSetpoint, rotateOffset;
	bool velocityControl, rotationalControl;
	DrivetrainPID(double rightSetpoint, double leftSetpoint, double strafeSetpoint, bool velocityControl, bool rotationalControl = false, double rotateOffset = 0 );
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // DrivetrainPID_H
