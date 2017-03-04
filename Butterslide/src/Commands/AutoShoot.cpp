/*
 * AutoShoot.cpp
 *
 *  Created on: Feb 27, 2017
 *      Author: Dylan
 */

#include "AutoShoot.h"
#include "ShootSetPointBB.h"
#include "Feed.h"
#include "RotateToAngle.h"
#include <cmath>

AutoShoot::AutoShoot() {
	double distanceFromBoilerY = 0, distanceFromBoilerX = 0, shooterSpeed = 0, feedSpeed = -.5, angle = 0;

		//Because the following is executed immediately, might not need to be put in a command
		//**************** Start TODO  Command**********************
		//Get x and y offsets of boiler from vision
		distanceFromBoilerX = Robot::table->GetNumber("Distance From Boiler X", 0.0);
		distanceFromBoilerY = Robot::table->GetNumber("Distance From Boiler Y", 0.0);
		angle = atan(distanceFromBoilerX/distanceFromBoilerY)/3.14159*180;
		//**************** End TODO Command **********************

		AddSequential(new RotateToAngle(angle));

		//Wait so vision distance from boiler is accurate
		AddSequential(new WaitCommand(.1));

		//********************** Start TODO Command ****************************
		//Get vision info for distance
		distanceFromBoilerY = Robot::table->GetNumber("Distance From Boiler Y", 0.0);

		//Calculate shooter speed
		shooterSpeed = Robot::rpg->CalculateShooterSpeedFPS(distanceFromBoilerY);

		//Calculate feed speed, possibly do it discretely (if within this range, round down to this)
		//feedSpeed = calculatedFeedSpeed(shooterSpeed);
		//********************** End TODO Command ********************************

		//Start up shooter at calculated shooter speed
		AddParallel(new ShootSetPointBB(shooterSpeed*12*1024/(4*3.14159)));

		//Give the shooter time to get up to speed
		AddSequential(new WaitCommand(.25));


		//Turn the feeder on
		AddParallel(new Feed(feedSpeed));

}

AutoShoot::~AutoShoot() {

}

