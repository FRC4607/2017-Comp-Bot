#include "CANTalon.h"

class CANTalonSpecial: CANTalon {
private:
public:
	CANTalonSpecial(int);
	~CANTalonSpecial();
	bool rotatePID;
	double rotateAdjustment;
	void PIDWrite(double);
	double GetRotateAdjustment();
	void SetRotateAdjustment(double);
};
