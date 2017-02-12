#ifndef EnableDriving_H
#define EnableDriving_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

class EnableDriving : public Command {
public:
	EnableDriving();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // EnableDriving_H
