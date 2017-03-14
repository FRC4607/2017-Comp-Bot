/*
 * Auto_Drive.cpp
 *
 *  Created on: Feb 23, 2016
 *      Author: CIS 4607
 */




#include "Auto_Drive.h"
#include "AutonomousCommand.h"
#include "DrivetrainPID.h"
#include "RotateToAngle.h"
#include "AllignWithPeg.h"

#include "../Robot.h"







AutoDrive::AutoDrive(StartingPosition startingPosition) {


	if (startingPosition == Middle) {
		 AddSequential(new DrivetrainPID(5*12, 5*12, 0, false, false, 0));
		 AddSequential(new RotateToAngle(90));
	}

	else if (startingPosition == Left) {
		AddSequential(new DrivetrainPID(5*12+10, 5*12+10, 0, false, false, 0));
		AddSequential(new RotateToAngle(150));
	}

	else if (startingPosition == Right) {
		AddSequential(new DrivetrainPID(5*12+10, 5*12+10, 0, false, false, 0));
		AddSequential(new RotateToAngle(30));
	}
	//Allign via strafing
	AddSequential(new AllignWithPeg(AllignWithPeg::CENTER));

	//Allign via driving onto the peg
	AddSequential(new AllignWithPeg(AllignWithPeg::DRIVE_FORWARD));
}
