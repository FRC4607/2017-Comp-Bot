#include "AllignWithPeg.h"
#include "DrivetrainPID.h"

AllignWithPeg::AllignWithPeg(int mode) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::drivetrain.get());
	this->mode = mode;
}

// Called just before this Command runs the first time
void AllignWithPeg::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void AllignWithPeg::Execute() {
	//If when it was strafing it had only seen a single lift peg target to strafe, it will strafe once more upon seeing the other
	if (!done) {
		//If it is going to strafe again, don't do so until the current strafing is over
		if (!Robot::drivetrain->drivetrainPIDRunning) {

			//Update calculation of spring's location
			Robot::vision->AllignWithGearPeg();

			//Aligning to the gear peg by strafing
			if (mode == 1) {
				double strafeDistance = Robot::drivetrain->springX;
				Scheduler::GetInstance()->AddCommand(
						new DrivetrainPID(strafeDistance, strafeDistance, 0,
								false, false, 0));
			}
			//Aligning to the gear peg by driving at the forward to the spring
			if (mode == 2) {
				double driveforwardDistance = Robot::drivetrain->springY
						- STOPPING_DISTANCE_FROM_AIRSHIP;
				Scheduler::GetInstance()->AddCommand(
						new DrivetrainPID(0, 0, driveforwardDistance, false,
								false, 0));
			}

		}
		//If the robot is done moving and if strafing it saw both vision targets, end, otherwise continue
		else {
			if (mode == 1) {

				done = Robot::vision->bothTargets;
			}
			if (mode == 2) {
				done = true;
			}
		}
	}
}

// Make this return true when this Command no longer needs to run execute()
bool AllignWithPeg::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void AllignWithPeg::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AllignWithPeg::Interrupted() {

}
