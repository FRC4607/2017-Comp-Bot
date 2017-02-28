/*
 * FieldOrientedPIDSource.cpp
 *
 *  Created on: Feb 17, 2017
 *      Author: Dylan
 */

#include "FieldOrientedPIDSource.h"

FieldOrientedPIDSource::FieldOrientedPIDSource(std::shared_ptr<Encoder> primary, std::shared_ptr<Encoder> secondary) {
	// TODO Auto-generated constructor stub
	this->primary = primary;
	this->secondary = secondary;

	initialAngle = 0;
	currentAngle = 0;
	primaryPrior = 0;
	secondaryPrior = 0;
	total = 0;
}
double FieldOrientedPIDSource::PIDGet(){
	double primaryDiff, secondaryDiff, totalDiff;
	primaryDiff = primary->Get() - primaryPrior;
	secondaryDiff = secondary->Get() - secondaryPrior;
	totalDiff = cos((initialAngle-currentAngle)/180*3.14159)*primaryDiff+sin((initialAngle-currentAngle)*3.14159)*secondaryDiff;
	total += totalDiff;
	return 1;
}

FieldOrientedPIDSource::~FieldOrientedPIDSource() {
	// TODO Auto-generated destructor stub
}
