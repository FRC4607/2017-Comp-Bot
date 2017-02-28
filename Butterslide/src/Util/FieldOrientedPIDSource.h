/*
 * FieldOrientedPIDSource.h
 *
 *  Created on: Feb 17, 2017
 *      Author: Dylan
 */

#ifndef SRC_UTIL_FIELDORIENTEDPIDSOURCE_H_
#define SRC_UTIL_FIELDORIENTEDPIDSOURCE_H_

#include <PIDSource.h>
#include <Encoder.h>

class FieldOrientedPIDSource: public frc::PIDSource {
public:
	FieldOrientedPIDSource(std::shared_ptr<Encoder>, std::shared_ptr<Encoder>);
	virtual ~FieldOrientedPIDSource();
	double PIDGet();
	double initialAngle, currentAngle, primaryPrior, secondaryPrior, total;
	std::shared_ptr<Encoder> primary, secondary;
};

#endif /* SRC_UTIL_FIELDORIENTEDPIDSOURCE_H_ */
