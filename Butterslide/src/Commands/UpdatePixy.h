/*
 * UpdatePixy.h
 *
 *  Created on: Mar 1, 2017
 *      Author: Dylan
 */

#ifndef SRC_COMMANDS_UPDATEPIXY_H_
#define SRC_COMMANDS_UPDATEPIXY_H_

#include "../Robot.h"
#include "Commands/Subsystem.h"

class UpdatePixy: public Command {
public:
	UpdatePixy();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif /* SRC_COMMANDS_UPDATEPIXY_H_ */
