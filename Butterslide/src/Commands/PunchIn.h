#ifndef PunchIn_H
#define PunchIn_H

#include "../Robot.h"
#include "Commands/Subsystem.h"

class PunchIn : public Command {
public:
	PunchIn();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // PunchIn_H
