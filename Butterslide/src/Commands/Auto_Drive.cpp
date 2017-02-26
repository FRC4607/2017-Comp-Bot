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

#include "../Robot.h"







AutoDrive::AutoDrive(StartingPosition startingPosition) {

double strafeDistance;
double driveForwardDistance;
const double STOPPING_DISTANCE_FROM_AIRSHIP = 2;

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

	//Robot::drivetrain->AllignWithGearPeg();

	strafeDistance = Robot::drivetrain->springX;

	AddSequential(new DrivetrainPID(strafeDistance, strafeDistance, 0, false, false, 0));
	//Robot::drivetrain->AllignWithGearPeg();
	driveForwardDistance = Robot::drivetrain->springY - STOPPING_DISTANCE_FROM_AIRSHIP;
	//AddSequential(new DrivetrainPID(0, 0, driveForwardDistance, false, false, 0));
}
