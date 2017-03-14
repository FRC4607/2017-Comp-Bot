#ifndef AllignWithPeg_H
#define AllignWithPeg_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

class AllignWithPeg : public Command {
public:
	int mode;
	static int const CENTER = 1, DRIVE_FORWARD = 2;
	bool done = false;
	const double STOPPING_DISTANCE_FROM_AIRSHIP = 2;
	AllignWithPeg(int mode);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // AllignWithPeg_H
