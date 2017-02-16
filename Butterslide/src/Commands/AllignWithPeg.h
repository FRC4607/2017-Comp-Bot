#ifndef AllignWithPeg_H
#define AllignWithPeg_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

class AllignWithPeg : public Command {
public:
	AllignWithPeg();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // AllignWithPeg_H
