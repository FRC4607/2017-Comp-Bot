#include "ShootSetPointBB.h"

ShootSetPointBB::ShootSetPointBB(double setpoint) {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  this->setpoint=setpoint;
}

// Called just before this Command runs the first time
void ShootSetPointBB::Initialize() {
/*  Robot::rpg->SetSetpoint(setpoint);
  Robot::rpg->Enable();
*/
}

// Called repeatedly when this Command is scheduled to run
void ShootSetPointBB::Execute() {
  SmartDashboard::PutNumber("Shooter SRX Error:", setpoint - RobotMap::rpg1->GetEncVel());
  if(RobotMap::rpg1->GetEncVel() > setpoint){
	  RobotMap::rpg1->Set(0);
  }
  else {
	  RobotMap::rpg1->Set(1);
  }

}

// Make this return true when this Command no longer needs to run execute()
bool ShootSetPointBB::IsFinished() {
  //return Robot::rpg->OnTarget();
  return Robot::oi->getDriver()->GetRawButton(1);
}

// Called once after isFinished returns true
void ShootSetPointBB::End() {
  //Robot::rpg->Disable();
  RobotMap::rpg1->SetControlMode(CANSpeedController::kPercentVbus);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShootSetPointBB::Interrupted() {
  End();
}
