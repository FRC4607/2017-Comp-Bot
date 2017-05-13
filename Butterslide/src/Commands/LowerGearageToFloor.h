#ifndef LowerGearageToFloor_H
#define LowerGearageToFloor_H

#include "../Robot.h"
#include "Commands/Subsystem.h"

class LowerGearageToFloor : public Command {
public:
	LowerGearageToFloor();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // LowerGearageToFloor_H
