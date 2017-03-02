/*
 * PixyPIDSource.h
 *
 *  Created on: Mar 1, 2017
 *      Author: Dylan
 */

#ifndef SRC_UTIL_PIXYPIDSOURCE_H_
#define SRC_UTIL_PIXYPIDSOURCE_H_

#include <PIDSource.h>

class PixyPIDSource: public frc::PIDSource {
public:
	PixyPIDSource();
	virtual ~PixyPIDSource();
	double PIDGet();
};

#endif /* SRC_UTIL_PIXYPIDSOURCE_H_ */
