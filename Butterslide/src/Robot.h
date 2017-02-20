// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef _ROBOT_H
#define _ROBOT_H

#include "WPILib.h"
#include "Commands/Command.h"
#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
#include "Subsystems/Shooter.h"
#include "Subsystems/Intake.h"
#include <vector>
#include "Commands/Auto_Drive.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "Commands/AutonomousCommand.h"
#include "Subsystems/Drivetrain.h"
#include "Subsystems/Pneumatics.h"

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "OI.h"
#include "TPixy.h"
#include "PixyI2C.h"

class Robot : public IterativeRobot {
public:
	std::unique_ptr<Command> autonomousCommand;
	static std::unique_ptr<OI> oi;
	LiveWindow *lw = LiveWindow::GetInstance();
	static std::shared_ptr<NetworkTable> table;
    static std::shared_ptr<Drivetrain> drivetrain;
    static std::shared_ptr<Pneumatics> pneumatics;
    static std::shared_ptr<Intake> ammo;
    static std::shared_ptr<Shooter> rpg;
    std::unique_ptr<Command> driveAnd {
    		new AutoDrive(0) };
    	std::unique_ptr<Command> driveForwardAuto { new AutoDrive(-.5) };
    SendableChooser<Command*> autoChooser;
    double autoSpeed;
    Robot();
	virtual void RobotInit();
	virtual void DisabledInit();
	virtual void DisabledPeriodic();
	virtual void AutonomousInit();
	virtual void AutonomousPeriodic();
	virtual void TeleopInit();
	virtual void TeleopPeriodic();
	virtual void TestPeriodic();
	virtual void RobotPeriodic();
	void SmartDashboardStuff();
};
#endif
