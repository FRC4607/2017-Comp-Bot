#ifndef Shooting_H
#define Shooting_H

#include "../Robot.h"
#include "Commands/Subsystem.h"

class Shooting : public Command {
public:
	Shooting();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // Shooting_H
