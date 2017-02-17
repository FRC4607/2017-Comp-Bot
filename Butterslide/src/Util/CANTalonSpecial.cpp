#include "CANTalonSpecial.h"

CANTalonSpecial::CANTalonSpecial(int deviceID) : CANTalon(deviceID){

}
CANTalonSpecial::~CANTalonSpecial(){

}
void CANTalonSpecial::PIDWrite(double output){

	this->Set(output);
}
