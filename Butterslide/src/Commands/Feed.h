#ifndef Feed_H
#define Feed_H

#include "../Robot.h"
#include "Commands/Subsystem.h"

class Feed : public Command {
public:
	Feed();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // Feed_H
