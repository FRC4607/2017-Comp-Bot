#include "Vision.h"
#include "../RobotMap.h"
#include "PixySPI.h"
#include <SmartDashboard/SendableChooser.h>
#include "../Commands/UpdatePixy.h"

PixySPI *pixy1;
SPI::Port port = SPI::Port::kOnboardCS0;
PixySPI::PacketMapSet *packets;

Vision::Vision() :
								Subsystem("Vision") {
	// Open a pipeline to a Pixy camera.
	pixy1 = new PixySPI(port);
	packets = pixy1->getPackets();
	packetBuffer = packets;
	SmartDashboard::PutString("Vision: Object created", "true");
}

void Vision::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	SetDefaultCommand(new UpdatePixy());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

// These values are the default if you instantiate a PixySPI without arguments.
// To create multiple PixySPI objects and thus use multiple Pixy cameras via SPI
// Copy the items below, change variable names as needed and especially change
// the SPI port used eg; Port.kOnboardCS[0-3] or Port.kMXP

void Vision::testPixy1() {
	// Get the packets from the pixy.
	int ret = pixy1->readPackets();
	pixy1->setDebugLvl(0);

	/*SmartDashboard::PutString("Pixy Vision: packets size: ", std::to_string(packets->size()));

	 for(int i = 1; i <= pixy1->getPixySigCount() ; i++) {
	 SmartDashboard::PutString("Pixy Vision: Signature: ", std::to_string(i));

	 SmartDashboard::PutString("Pixy Vision: packet: " + std::to_string(i) + ": size: ", std::to_string(packets->at(i).size()));

	 // Loop through the packets for this signature.
	 for(int j=0; j < packets->at(i).size(); j++) {
	 SmartDashboard::PutString("Pixy Vision: " + std::to_string(i) + ": X: ", std::to_string(packets->at(i).at(j).X));
	 SmartDashboard::PutString("Pixy Vision: " + std::to_string(i) + ": Y: ", std::to_string(packets->at(i).at(j).Y));
	 SmartDashboard::PutString("Pixy Vision: " + std::to_string(i) + ": Width: ", std::to_string(packets->at(i).at(j).Width));
	 SmartDashboard::PutString("Pixy Vision: " + std::to_string(i) + ": Height: ", std::to_string(packets->at(i).at(j).Height));
	 }
	 }
	 */
	int area = 0, tempMax1 = -1, tempMax2 = -2;
	//for (int i = 1; i <= pixy1->getPixySigCount(); i++) {

	// Loop through the packets for this signature.
	for (int j = 0; j < packets->at(1).size(); j++) {
		area = packets->at(1).at(j).Height * packets->at(1).at(j).Width;
		if (area > tempMax1) {
			tempMax2 = tempMax1;
			tempMax1 = j;
		} else if (area > tempMax2) {
			tempMax2 = j;
		}
	}
	//}
	empty = packets->empty();
	max1 = tempMax1;
	max2 = tempMax2;
	packetBuffer = packets;

}

void Vision::GetPacketsSig(int i){

	packets = pixy1->getPackets();

	int area = 0, tempMax1 = -1, tempMax2 = -2;
	for (int j = 0; j < packets->at(i).size(); j++) {
		area = packets->at(i).at(j).Height * packets->at(i).at(j).Width;
		if (area > tempMax1) {
			tempMax2 = tempMax1;
			tempMax1 = j;
		} else if (area > tempMax2) {
			tempMax2 = j;
		}
	}
	empty = packets->empty();
	max1 = tempMax1;
	max2 = tempMax2;
	packetBuffer = packets;

}
void Vision::AllignWithGearPeg() {

	//Vertical field of view of the zed,
	// base on formula from http://www.rjdown.co.uk/projects/bfbc2/fovcalculator.php
	const float PIXYCAM_HEIGHT_FT = 2; //The height of the Pixycam mounted on the robot in ft
	double zedValue, xPixels, yPixels, z, b, xdc, ydc, xPixels2, yPixels2;
	const float PI = 3.14159;
	double width = 640; //Width of PixyCam image
	double height = 400; //Height of PixyCam image
	double VFOV = 47;
	double HFOV = 75;
	double x2, x, y, y2;

	this->GetPacketsSig(1);

	if (!Robot::vision->empty) {
		//These are going to be set to values from the pixy later on. Set to 1 for the time being, not an actual value.

		xPixels = packetBuffer->at(1).at(max1).X;
		yPixels = packetBuffer->at(1).at(max1).Y;

		//Convert pixel and zed values to X,Y,Z offsets in  feet

		xdc = xPixels - width / 2; //Pixels from the center the object center is in the x direction
		ydc = height / 2 - yPixels; //Pixels from the center the object center is in the y direction

		z = 13.25; //z is height of the center of the tape target in inches
		zedValue = (z - PIXYCAM_HEIGHT_FT * 12) / sin(ydc * VFOV / height);

		//b is the diagonal from the zed to the observed point at the same height as the camera
		b = sqrt(pow(zedValue, 2) - pow(z, 2)); //Pythagorean Theoremn

		x = b * sin((xdc * HFOV / width) * PI / 180); //Law of Sines
		y = b * sin((90 - xdc * HFOV / width) * PI / 180); //Law of Sines

		if (packetBuffer->at(1).size() < 2) {
			springX = x;
			springY = y;
			bothTargets = false;

		} else {
			xPixels2 = packetBuffer->at(1).at(max2).X;
			yPixels2 = packetBuffer->at(1).at(max2).Y;

			xdc = xPixels2 - width / 2; //Pixels from the center the object center is in the x direction
			ydc = height / 2 - yPixels2; //Pixels from the center the object center is in the y direction

			zedValue = (z - PIXYCAM_HEIGHT_FT * 12) / sin(ydc * VFOV / height);

			//b is the diagonal from the zed to the observed point at the same height as the camera
			b = sqrt(pow(zedValue, 2) - pow(z, 2)); //Pythagorean Theorem

			x2 = b * sin((xdc * HFOV / width) * PI / 180); //Law of Sines
			y2 = b * sin((90 - xdc * HFOV / width) * PI / 180); //Law of Sines
			springX = (x2 + x) / 2;
			springY = (y2 + y) / 2;
			bothTargets = true;
		}
	}
}
void Vision::displayPixy() {
	// Get the packets from the pixy.
	int ret = pixy1->readPackets();
	pixy1->setDebugLvl(0);

	SmartDashboard::PutString("Pixy Vision: packets size: ", std::to_string(packets->size()));

	for(int i = 1; i <= pixy1->getPixySigCount() ; i++) {
		SmartDashboard::PutString("Pixy Vision: Signature: ", std::to_string(i));

		SmartDashboard::PutString("Pixy Vision: packet: " + std::to_string(i) + ": size: ", std::to_string(packets->at(i).size()));

		// Loop through the packets for this signature.
		for(int j=0; j < packets->at(i).size(); j++) {
			SmartDashboard::PutString("Pixy Vision: " + std::to_string(i) + ": X: ", std::to_string(packets->at(i).at(j).X));
			SmartDashboard::PutString("Pixy Vision: " + std::to_string(i) + ": Y: ", std::to_string(packets->at(i).at(j).Y));
			SmartDashboard::PutString("Pixy Vision: " + std::to_string(i) + ": Width: ", std::to_string(packets->at(i).at(j).Width));
			SmartDashboard::PutString("Pixy Vision: " + std::to_string(i) + ": Height: ", std::to_string(packets->at(i).at(j).Height));
		}
	}
}

void Vision::displayPixy(int i) {
	// Get the packets from the pixy.
	int ret = pixy1->readPackets();
	pixy1->setDebugLvl(0);

	SmartDashboard::PutString("Pixy Vision: packets size: ", std::to_string(packets->size()));

	SmartDashboard::PutString("Pixy Vision: Signature: ", std::to_string(i));

	SmartDashboard::PutString("Pixy Vision: packet: " + std::to_string(i) + ": size: ", std::to_string(packets->at(i).size()));

	// Loop through the packets for this signature.
	for(int j=0; j < packets->at(i).size(); j++) {
		SmartDashboard::PutString("Pixy Vision: " + std::to_string(i) + ": X: ", std::to_string(packets->at(i).at(j).X));
		SmartDashboard::PutString("Pixy Vision: " + std::to_string(i) + ": Y: ", std::to_string(packets->at(i).at(j).Y));
		SmartDashboard::PutString("Pixy Vision: " + std::to_string(i) + ": Width: ", std::to_string(packets->at(i).at(j).Width));
		SmartDashboard::PutString("Pixy Vision: " + std::to_string(i) + ": Height: ", std::to_string(packets->at(i).at(j).Height));
	}
}
