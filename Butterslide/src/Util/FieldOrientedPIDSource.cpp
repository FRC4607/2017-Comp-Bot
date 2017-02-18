/*
 * FieldOrientedPIDSource.cpp
 *
 *  Created on: Feb 17, 2017
 *      Author: Dylan
 */

#include "FieldOrientedPIDSource.h"

FieldOrientedPIDSource::FieldOrientedPIDSource() {
	// TODO Auto-generated constructor stub
//	this->primary = primary;
	//this->secondary = secondary;
	initialAngle = 0;
	currentAngle = 0;
	primaryPrior = 0;
	secondaryPrior = 0;
	total = 0;
}
double FieldOrientedPIDSource::PIDGet(){
	double primaryDiff, secondaryDiff, totalDiff;
	//primaryDiff = primary.Get() - primaryPrior;
//	secondaryDiff = secondary.Get() - secondaryPrior;
//	totalDiff = cos(initialAngle-currentAngle)*primaryDiff+sin(initialAngle-currentAngle)*secondaryDiff;
//	total += totalDiff;
	return 1;
}

FieldOrientedPIDSource::~FieldOrientedPIDSource() {
	// TODO Auto-generated destructor stub
}

