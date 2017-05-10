// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Robot.h"
//#include "TPixy.h"
//#include "PixyI2C.h"
#include "Commands/AutonomousCommand.h"
#include "Commands/AutoShoot.h"
#include "Commands/PunchIn.h"
#include "Commands/PunchOut.h"
#include "Commands/AutoShoot.h"
#include "Commands/HopperAuto.h"


// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
std::shared_ptr<Drivetrain> Robot::drivetrain;
std::shared_ptr<Pneumatics> Robot::pneumatics;
std::shared_ptr<Shooter> Robot::rpg;
std::shared_ptr<Intake> Robot::ammo;
std::unique_ptr<OI> Robot::oi;
std::shared_ptr<NetworkTable> Robot::table;
std::shared_ptr<Vision> Robot::vision;
std::shared_ptr<VisionCheck> Robot::visionCheck;
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
Robot::Robot(){
	table->GetTable("GRIP/myContoursReport");
	autoSpeed = 0;
}
void Robot::RobotInit() {
	RobotMap::init();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	drivetrain.reset(new Drivetrain());
	pneumatics.reset(new Pneumatics());
	rpg.reset(new Shooter());
	ammo.reset(new Intake());
	vision.reset(new Vision());
	visionCheck.reset(new VisionCheck());
	CameraServer::GetInstance()->StartAutomaticCapture();
	visionCheck->CreateCameraEntriesOnSD();

	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	// This MUST be here. If the OI creates Commands (which it very likely
	// will), constructing it during the construction of CommandBase (from
	// which commands extend), subsystems are not guaranteed to be
	// yet. Thus, their requires() statements may grab null pointers. Bad
	// news. Don't move it.
	oi.reset(new OI());


	// instantiate the command used for the autonomous period
	//	SmartDashboard::GetNumber("Auto Speed", autoSpeed);

	//autoChooser.AddDefault("Cross the Street Mitchel", crossTheStreetMitchel.get());
	//	AutoForward* goat = new AutoForward;

	//autonomousCommand.reset(new AutoForward(-.4 , 3));
	//When ready to try 10kPa auto uncomment next line and comment out above line
	//autonomousCommand.reset(new AutoShoot());
	autoChooser.AddDefault("Cross Base Line Forward", new AutoForward(-.4 , 3));
	autoChooser.AddObject("Cross Base Line Backward", new AutoForward(.4 , 3));
	autoChooser.AddObject("Hopper Shoot Blue", new HopperAutoRed());
	autoChooser.AddObject("AutoShoot Command", new AutoShoot());

	SmartDashboard::PutData("Auto Mode", &autoChooser);

	std::thread visionThread = visionCheck->VisionThread();
	visionThread.detach();

}

/**
 * This function is called when the disabled button is hit.
 * You can use it to reset subsystems before shutting down.
 */
void Robot::DisabledInit(){

}

void Robot::DisabledPeriodic() {
	Scheduler::GetInstance()->Run();
	Robot::vision->displayPixy();
}

void Robot::RobotPeriodic(){
	//	std::vector<double> xArray = table->GetNumberArray("x", llvm::ArrayRef<double>());
	//	std::vector<double> yArray = table->GetNumberArray("y", llvm::ArrayRef<double>());
	//	std::vector<double> widthArray = table->GetNumberArray("width", llvm::ArrayRef<double>());
	//	std::vector<double> heightArray = table->GetNumberArray("height", llvm::ArrayRef<double>());
	Robot::vision->displayPixy();
	visionCheck->HouseKeeping();
}

void Robot::AutonomousInit() {
	autonomousCommand = (std::unique_ptr<Command>)autoChooser.GetSelected();
	autonomousCommand->Start();
}

void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
	Robot::vision->displayPixy();
}

void Robot::TeleopInit() {
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// these lines or comment it out.
	//if (autonomousCommand.get() != nullptr)
	//autonomousCommand->Cancel();
}

void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();
	SmartDashboardStuff();
	Robot::vision->displayPixy();
	float xGo, yGo = 0;

	//	if ((visionCheck->HighGoalDistance() <= (desiredDistance * 1.1)) && (visionCheck->HighGoalDistance() >= (desiredDistance * .9))) {
	//		// Deadzone
	//		yGo = 0;
	//	}
	//	else if (desiredDistance > visionCheck->HighGoalDistance()) {
	//		yGo = .35;
	//	}
	//	else if (desiredDistance < visionCheck->HighGoalDistance()) {
	//		yGo = -.35;
	//	}
	//
	//	if ((visionCheck->HighGoalPosX() <= (desiredX * 1.1)) && (visionCheck->HighGoalPosX() >= (desiredX * .9))) {
	//		// Deadzone
	//		xGo = 0;
	//	}
	//	else if (desiredX > visionCheck->HighGoalPosX()) {
	//		xGo = .35;
	//	}
	//	else if (desiredX < visionCheck->HighGoalPosX()) {
	//		xGo = - .35;
	//	}
	//
	//	drivetrain->DrivingWithVision(xGo,yGo);
}

void Robot::TestPeriodic() {
	lw->Run();
}


void Robot::SmartDashboardStuff() {

	std::shared_ptr<AHRS> ahrs = RobotMap::drivetrainAHRS;
	std::shared_ptr<Encoder> encoderFrontLeft = RobotMap::drivetrainEncoderRearLeft;
	std::shared_ptr<Encoder> encoderFrontRight = RobotMap::drivetrainEncoderRearRight;
	std::shared_ptr<Encoder> encoderRightStrafe = RobotMap::drivetrainEncoderRightStrafe;

	SmartDashboard::PutBoolean( "IMU_Connected",        ahrs->IsConnected());
	SmartDashboard::PutNumber(  "IMU_Yaw",              ahrs->GetYaw());
	/*        SmartDashboard::PutNumber(  "IMU_Pitch",            ahrs->GetPitch());
	        SmartDashboard::PutNumber(  "IMU_Roll",             ahrs->GetRoll());
	        SmartDashboard::PutNumber(  "IMU_CompassHeading",   ahrs->GetCompassHeading());
	        SmartDashboard::PutNumber(  "IMU_Update_Count",     ahrs->GetUpdateCount());
	        SmartDashboard::PutNumber(  "IMU_Byte_Count",       ahrs->GetByteCount());
	 */
	/* These functions are compatible w/the WPI Gyro Class */
	SmartDashboard::PutNumber(  "IMU_TotalYaw",         ahrs->GetAngle());
	SmartDashboard::PutNumber(  "IMU_YawRateDPS",       ahrs->GetRate());

	/*        SmartDashboard::PutNumber(  "IMU_Accel_X",          ahrs->GetWorldLinearAccelX());
	        SmartDashboard::PutNumber(  "IMU_Accel_Y",          ahrs->GetWorldLinearAccelY());
	        SmartDashboard::PutBoolean( "IMU_IsMoving",         ahrs->IsMoving());
	        SmartDashboard::PutNumber(  "IMU_Temp_C",           ahrs->GetTempC());
	        SmartDashboard::PutBoolean( "IMU_IsCalibrating",    ahrs->IsCalibrating());
	 */
	SmartDashboard::PutNumber(  "Velocity_X",           ahrs->GetVelocityX() );
	SmartDashboard::PutNumber(  "Velocity_Y",           ahrs->GetVelocityY() );
	SmartDashboard::PutNumber(  "Displacement_X",       ahrs->GetDisplacementX() );
	SmartDashboard::PutNumber(  "Displacement_Y",       ahrs->GetDisplacementY() );

	/* Display Raw Gyro/Accelerometer/Magnetometer Values                       */
	/* NOTE:  These values are not normally necessary, but are made available   */
	/* for advanced users.  Before using this data, please consider whether     */
	/* the processed data (see above) will suit your needs.                     */

	SmartDashboard::PutNumber(  "RawGyro_X",            ahrs->GetRawGyroX());
	SmartDashboard::PutNumber(  "RawGyro_Y",            ahrs->GetRawGyroY());
	SmartDashboard::PutNumber(  "RawGyro_Z",            ahrs->GetRawGyroZ());
	/*   SmartDashboard::PutNumber(  "RawAccel_X",           ahrs->GetRawAccelX());
	        SmartDashboard::PutNumber(  "RawAccel_Y",           ahrs->GetRawAccelY());
	        SmartDashboard::PutNumber(  "RawAccel_Z",           ahrs->GetRawAccelZ());
	        SmartDashboard::PutNumber(  "RawMag_X",             ahrs->GetRawMagX());
	        SmartDashboard::PutNumber(  "RawMag_Y",             ahrs->GetRawMagY());
	        SmartDashboard::PutNumber(  "RawMag_Z",             ahrs->GetRawMagZ());
	        SmartDashboard::PutNumber(  "IMU_Temp_C",           ahrs->GetTempC());
	 */
	/* Omnimount Yaw Axis Information                                           */
	/* For more info, see http://navx-mxp.kauailabs.com/installation/omnimount  */
	AHRS::BoardYawAxis yaw_axis = ahrs->GetBoardYawAxis();
	SmartDashboard::PutString(  "YawAxisDirection",     yaw_axis.up ? "Up" : "Down" );
	SmartDashboard::PutNumber(  "YawAxis",              yaw_axis.board_axis );

	/* Sensor Board Information                                                 */
	SmartDashboard::PutString(  "FirmwareVersion",      ahrs->GetFirmwareVersion());

	/* Quaternion Data                                                          */
	/* Quaternions are fascinating, and are the most compact representation of  */
	/* orientation data.  All of the Yaw, Pitch and Roll Values can be derived  */
	/* from the Quaternions.  If interested in motion processing, knowledge of  */
	/* Quaternions is highly recommended.                                       */
	/*	        SmartDashboard::PutNumber(  "QuaternionW",          ahrs->GetQuaternionW());
	        SmartDashboard::PutNumber(  "QuaternionX",          ahrs->GetQuaternionX());
	        SmartDashboard::PutNumber(  "QuaternionY",          ahrs->GetQuaternionY());
	 */   SmartDashboard::PutNumber(  "QuaternionZ",          ahrs->GetQuaternionZ());
	 SmartDashboard::PutNumber(  "EncoderFL",          encoderFrontLeft->Get());
	 SmartDashboard::PutNumber(  "EncoderFR",          encoderFrontRight->Get());
	 SmartDashboard::PutNumber(  "EncoderRS",          encoderRightStrafe->Get());
	 SmartDashboard::PutNumber(   "EncoderScaleFR",      encoderFrontRight->GetEncodingScale());
	 SmartDashboard::PutNumber(   "EncoderScaleFL",      encoderFrontLeft->GetEncodingScale());
	 SmartDashboard::PutNumber(   "EncoderPIDFL",      encoderFrontLeft->PIDGet());
	 SmartDashboard::PutNumber(   "EncoderPIDFR",      encoderFrontRight->PIDGet());
	 SmartDashboard::PutNumber(   "EncoderFLRate",       encoderFrontLeft->GetRate());
	 SmartDashboard::PutNumber(   "EncoderFRRate",       encoderFrontRight->GetRate());

	 SmartDashboard::PutNumber("Shooter Encoder Rate", RobotMap::rpg1->GetEncVel());
	 SmartDashboard::PutNumber("Shooter Speed", RobotMap::rpg1->GetSpeed());
}
START_ROBOT_CLASS(Robot);

