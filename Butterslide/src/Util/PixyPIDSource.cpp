/*
 * PixyPIDSource.cpp
 *
 *  Created on: Mar 1, 2017
 *      Author: Dylan
 */

#include "PixyPIDSource.h"
#include "../Robot.h"
PixyPIDSource::PixyPIDSource() {


}
double PixyPIDSource::PIDGet(){
	Robot::vision->AllignWithGearPeg();
	return Robot::vision->springY;
}
PixyPIDSource::~PixyPIDSource(){

}
