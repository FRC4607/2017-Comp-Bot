#ifndef Climbing_H
#define Climbing_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

class Climbing : public Command {
public:
	Climbing();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // Climbing_H
