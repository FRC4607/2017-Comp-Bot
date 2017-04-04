#include "HopperAuto.h"
#include "AutoShoot.h"
#include "ShootSetPoint.h"
#include "ShootSetPointBB.h"
#include "Shooting.h"
#include "Feed.h"
#include "RotateToAngle.h"
#include "Strafe.h"
#include "Suck.h"

HopperAutoRed::HopperAutoRed() {
	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.

	// To run multiple commands at the same time,
	// use AddParallel()
	// e.g. AddParallel(new Command1());
	//      AddSequential(new Command2());
	// Command1 and Command2 will run in parallel.

	// A command group will require all of the subsystems that each member
	// would require.
	// e.g. if Command1 requires chassis, and Command2 requires arm,
	// a CommandGroup containing them would require both the chassis and the
	// arm.


	//Cross the baseline
	AddSequential(new AutoForward(.3, 1));
	AddSequential(new WaitCommand(.5));

	//Strafe away from the wall to be able to rotate
	AddSequential(new Strafe(.7,2));
	AddSequential(new WaitCommand(2));

	//Rotate would be here!

	AddParallel(new ShootSetPoint(-2000), 10);
	AddSequential(new Suck(), 3);
	AddSequential(new WaitCommand(10));







}
