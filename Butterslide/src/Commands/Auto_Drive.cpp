/*
 * Auto_Drive.cpp
 *
 *  Created on: Feb 23, 2016
 *      Author: CIS 4607
 */




#include "Auto_Drive.h"
#include "AutonomousCommand.h"

#include "../Robot.h"


AutoDrive::AutoDrive(float speed) {
	this->speed=speed;
   AddSequential(new AutoForward(speed, 2));
   AddSequential(new AutoForward(-speed/8,2));


}
