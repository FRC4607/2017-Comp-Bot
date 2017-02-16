#include "CANTalon.h"

class CANTalonSpecial: CANTalon {
public:
	CANTalonSpecial();
	~CANTalonSpecial();
	void PIDWrite(double);
};
