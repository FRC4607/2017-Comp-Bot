#ifndef Suck_H
#define Suck_H

#include "../Robot.h"
#include "Commands/Subsystem.h"

class Suck : public Command {
public:
	Suck();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // Suck_H
