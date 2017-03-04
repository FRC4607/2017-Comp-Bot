/*
 * Strafe.h
 *
 *  Created on: Mar 3, 2017
 *      Author: Dylan
 */

#ifndef SRC_COMMANDS_STRAFE_H_
#define SRC_COMMANDS_STRAFE_H_


#include "../Robot.h"
#include "Commands/Subsystem.h"

class Strafe: public Command {
public:
	Strafe(double speed, double time);
	double speed, time;
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif /* SRC_COMMANDS_STRAFE_H_ */
