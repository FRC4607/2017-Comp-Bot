#ifndef SRXLib_H
#define SRXLib_H

#include "../Robot.h"
#include "Commands/Subsystem.h"

class SRXLib : public Command {
public:
	SRXLib();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // SRXLib_H
