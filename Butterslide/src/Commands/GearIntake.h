#ifndef GearIntake_H
#define GearIntake_H

#include "../Robot.h"
#include "Commands/Subsystem.h"

class GearIntake : public Command {
public:
	GearIntake();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // GearIntake_H
