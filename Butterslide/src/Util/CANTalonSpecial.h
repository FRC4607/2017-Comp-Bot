#include "CANTalon.h"

class CANTalonSpecial: CANTalon {
private:
public:
	CANTalonSpecial(int);
	~CANTalonSpecial();
	bool rotatePID;
	void PIDWrite(double);
	double GetRotateAdjustment();
	double SetRotateAdjustment();
};
