#ifndef CamDisplay_H
#define CamDisplay_H
#include <Commands/Subsystem.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <networktables/NetworkTable.h>
#include <SmartDashboard/SmartDashboard.h>
#include <tables/ITableListener.h>
#include "../RobotMap.h"

class CamDisplay : public Subsystem, public ITableListener {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	std::shared_ptr<NetworkTable> vnt;
	std::string cam_name;
	std::string nt_listen_name;
	int width;
	int height;
	void ValueChanged(ITable *, llvm::StringRef, std::shared_ptr<nt::Value>, bool) override;
	std::string image_string;
	cs::CvSource m_cs;

public:
	CamDisplay(std::shared_ptr<NetworkTable>, std::string, std::string, int, int);
	void InitDefaultCommand();
	llvm::StringRef GetImage();
};

#endif  // CamDisplay_H
