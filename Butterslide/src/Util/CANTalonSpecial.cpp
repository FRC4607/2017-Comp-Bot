/*
 * CANTalonSpecial is a class defined to allow for PID control to be with encoders while simultaneously controlling the angle
 */

#include "CANTalonSpecial.h"

CANTalonSpecial::CANTalonSpecial(int deviceID) : CANTalon(deviceID){
	rotatePID = false;
	rotateAdjustment = 0;
}
CANTalonSpecial::~CANTalonSpecial(){

}
void CANTalonSpecial::PIDWrite(double output){
	if(rotatePID){
		this->Set(output + rotateAdjustment);
	}
	else{
		this->Set(output);
	}
}
double CANTalonSpecial::GetRotateAdjustment(){
	return rotateAdjustment;
}
void CANTalonSpecial::SetRotateAdjustment(double rotateAdjustment){
	this->rotateAdjustment = rotateAdjustment;
}
