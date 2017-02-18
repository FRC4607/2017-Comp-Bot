/*
 * Auto_Drive.h
 *
 *  Created on: Feb 23, 2016
 *      Author: CIS 4607
 */

#ifndef AUTO_DRIVE_H_
#define AUTO_DRIVE_H_





#include "WPILib.h"

/**
 * Drive over the line and then shoot the ball. If the hot goal is not detected,
 * it will wait briefly.
 */
class AutoDrive: public CommandGroup {
private:
	float speed;
public:
	AutoDrive(float speed);
};

#endif
