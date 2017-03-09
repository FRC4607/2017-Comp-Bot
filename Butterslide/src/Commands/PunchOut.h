#ifndef PunchOut_H
#define PunchOut_H

#include "../Robot.h"
#include "Commands/Subsystem.h"

class PunchOut : public Command {
public:
	PunchOut();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // PunchOut_H
