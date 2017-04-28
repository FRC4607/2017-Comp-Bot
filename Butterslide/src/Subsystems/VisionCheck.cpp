// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.




#include "VisionCheck.h"
#include "../RobotMap.h"
#include <thread>
#include <chrono>

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

VisionCheck::VisionCheck() : Subsystem("VisionCheck") {
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	//highGoalPosition = RobotMap::visionCheckHighGoalPosition;

	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

	vnt = NetworkTable::GetTable("Vision");
}

void VisionCheck::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND


	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

void VisionCheck::PopulateHighGoalVals() {
	HighGoalPos = vnt->GetNumberArray("High Goal Pos", llvm::ArrayRef<double>());

	if (HighGoalPos.empty()) {
		SmartDashboard::PutString("Vision Tracker Status", "NO CONNECTION");
		HighGoalPos = llvm::ArrayRef<double>{0,0,0};
	}
	else {
		SmartDashboard::PutString("Vision Tracker Status", "ONLINE");
	}
}

float VisionCheck::HighGoalDistance() {
	return HighGoalPos[2];
}
float VisionCheck::HighGoalPosX() {
	return HighGoalPos[0];
}
float VisionCheck::HighGoalPosY() {
	return HighGoalPos[1];
}

void VisionCheck::DisplayValuesOnSD() {
	SmartDashboard::PutNumber("High Goal Distance", this->HighGoalDistance());
	SmartDashboard::PutNumber("High Goal X", this->HighGoalPosX());
	SmartDashboard::PutNumber("High Goal Y", this->HighGoalPosY());
}

void VisionCheck::CreateCameraEntriesOnSD() {
	SmartDashboard::PutNumber("H_MIN", 0);
	SmartDashboard::PutNumber("H_MAX", 255);
	SmartDashboard::PutNumber("S_MIN", 0);
	SmartDashboard::PutNumber("S_MAX", 255);
	SmartDashboard::PutNumber("V_MIN", 0);
	SmartDashboard::PutNumber("V_MAX", 255);
	SmartDashboard::PutNumber("Exposure", 100);

	SmartDashboard::SetPersistent("H_MIN");
	SmartDashboard::SetPersistent("H_MAX");
	SmartDashboard::SetPersistent("S_MIN");
	SmartDashboard::SetPersistent("S_MAX");
	SmartDashboard::SetPersistent("V_MIN");
	SmartDashboard::SetPersistent("V_MAX");
	SmartDashboard::SetPersistent("Exposure");
}

void VisionCheck::CheckForHSVUpdatesFromCore() {
	if (vnt->GetBoolean("HSVUpdate")) {
		// Have HSV Updates, pull them from NetworkTables.
		std::vector<double> HSVVals = vnt->GetNumberArray("HSVVals", -1);
		SmartDashboard::PutNumber("H_MIN", HSVVals.at(0));
		SmartDashboard::PutNumber("H_MAX", HSVVals.at(1));
		SmartDashboard::PutNumber("S_MIN", HSVVals.at(2));
		SmartDashboard::PutNumber("S_MAX", HSVVals.at(3));
		SmartDashboard::PutNumber("V_MIN", HSVVals.at(4));
		SmartDashboard::PutNumber("V_MAX", HSVVals.at(5));

		// Reset HSVUpdate to false now that we've acted on the new values.
		vnt->PutBoolean("HSVUpdate", false);
	}
}

void VisionCheck::SendHSVEntriesToTX1() {
	vnt->PutNumber("H_MIN", SmartDashboard::GetNumber("H_MIN", 0));
	vnt->PutNumber("H_MAX", SmartDashboard::GetNumber("H_MAX", 0));
	vnt->PutNumber("S_MIN", SmartDashboard::GetNumber("S_MIN", 0));
	vnt->PutNumber("S_MAX", SmartDashboard::GetNumber("S_MAX", 0));
	vnt->PutNumber("V_MIN", SmartDashboard::GetNumber("V_MIN", 0));
	vnt->PutNumber("V_MAX", SmartDashboard::GetNumber("V_MAX", 0));
}

void VisionCheck::SendCameraSettingsToTX1() {
	vnt->PutNumber("Exposure", SmartDashboard::GetNumber("Exposure", 100));
}

llvm::StringRef VisionCheck::GetImage() {
	return(vnt->GetRaw("hg_image", ""));
}

void VisionCheck::VisionThread() {
	zed_cam_server = CameraServer::GetInstance()->PutVideo("Zed", 702, 404);

	cv::Mat image_mat, image, output;
	std::string image_string = "";

	while(true) {
		image_string = vnt->GetRaw("hg_image", "");

		// Don't bother trying to convert a blank image_string.
		if (image_string == "") {
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
		else {
			std::vector<char> image_vector(image_string.begin(), image_string.end());

			cv::Mat image_mat(image_vector,true);
			cv::Mat image(cv::imdecode(image_mat, 1));
			cv::cvtColor(image, output, cv::COLOR_BGR2GRAY);
			zed_cam_server.PutFrame(output);
		}
	}
}

