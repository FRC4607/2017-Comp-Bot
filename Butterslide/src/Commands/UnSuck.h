#ifndef UnSuck_H
#define UnSuck_H

#include "../Robot.h"
#include "Commands/Subsystem.h"

class UnSuck : public Command {
public:
	UnSuck();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // UnSuck_H
