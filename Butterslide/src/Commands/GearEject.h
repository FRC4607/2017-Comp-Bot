#ifndef GearEject_H
#define GearEject_H

#include "../Robot.h"
#include "Commands/Subsystem.h"

class GearEject : public Command {
public:
	GearEject();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // GearEject_H
