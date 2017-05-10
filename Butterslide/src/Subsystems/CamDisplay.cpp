#include "CamDisplay.h"
#include <chrono>
#include <thread>

CamDisplay::CamDisplay(std::shared_ptr<NetworkTable> vnt,
		std::string cam_name,
		std::string nt_listen_name,
		int width,
		int height) : Subsystem("CamDisplay") {
	this->cam_name = cam_name;
	this->vnt = vnt;
	this->nt_listen_name = nt_listen_name;
	this->width = width;
	this->height = height;

	std::cout << "CamDisplay object for " << cam_name << " created." << std::endl;
	vnt->AddTableListener(nt_listen_name, this, true);
	m_cs = CameraServer::GetInstance()->PutVideo(cam_name, width, height);
}

void CamDisplay::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

llvm::StringRef CamDisplay::GetImage() {
	return(vnt->GetRaw(nt_listen_name, ""));
}

void CamDisplay::ValueChanged(ITable * table, llvm::StringRef key, std::shared_ptr<nt::Value> value, bool isNew) {
	image_string = value->GetRaw();

	// Don't bother trying to convert a blank image_string.
	if (image_string == "") {
		//std::cout << "empty: nt_listen_name: " << nt_listen_name << " cam_name: " << cam_name << " image_string.size: " << std::to_string(image_string.size()) << std::endl;
		//std::this_thread::sleep_for(std::chrono::milliseconds(20));
		//std::cout << "Sleeping" << std::endl;
	}
	else {
		//std::cout << "nt_listen_name: " << nt_listen_name << " cam_name: " << cam_name << " image_string.size: " << std::to_string(image_string.size()) << std::endl;
		std::vector<char> image_vector(image_string.begin(), image_string.end());

		cv::Mat image_mat(image_vector,true);
		cv::Mat image(cv::imdecode(image_mat, 1));
		m_cs.PutFrame(image);
	}
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
