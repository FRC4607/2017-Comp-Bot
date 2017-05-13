#ifndef RaiseGearageVertical_H
#define RaiseGearageVertical_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

class RaiseGearageVertical : public Command {
public:
	RaiseGearageVertical();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // RaiseGearageVertical_H
