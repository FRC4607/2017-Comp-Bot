#ifndef PIXY_SPI_H
#define PIXY_SPI_H

#include <Commands/Subsystem.h>
#include "PixyPacket.h"
#include <iostream>
#include <map>
#include <vector>
#include <SPI.h>
#include "WPILib.h"

class PixySPI: public Subsystem {
public:
	PixySPI(SPI::Port);
	virtual ~PixySPI() = default;
	//void InitDefaultCommand() override;

	// Evil I know, but need these here to allow use outside of file.
	typedef std::vector<PixyPacket> PacketSet;
	typedef std::map<int, PacketSet> PacketMapSet;
	typedef std::vector<std::vector<unsigned short int> > BlockSet;

	// Variables used for pixy comms, derived from https://github.com/omwah/pixy_rpi
	PacketMapSet *packets;

	int getPixySigCount(){return(PIXY_SIG_COUNT);}
	PacketMapSet* getPackets(){return(packets);}
	int readPackets();

	int getDebugLvl(){return(debug);}
	void setDebugLvl(int i){debug = i;}

private:
	SPI *pixy;
	bool skipStart = false;
	int debug = 0; // 0 - none, 1 - SmartDashboard, 2 - log to console/file
	long getWordCount = 0;
	long getStartCount = 0;
	long getBlockCount = 0;
	long readPacketsCount = 0;

	unsigned short int PIXY_SYNC_BYTE = 0x5a;
	unsigned short int PIXY_SYNC_BYTE_DATA = 0x5b;
	unsigned short int PIXY_OUTBUF_SIZE = 6;
	unsigned short int PIXY_MAXIMUM_ARRAYSIZE = 130;
	unsigned short int PIXY_START_WORD = 0xaa55;
	unsigned short int PIXY_START_WORDX = 0x55aa;
	unsigned short int BLOCK_LEN = 5;
	unsigned short int PIXY_SIG_COUNT = 7;

	std::queue<unsigned char> outBuf; // Future use for sending commands to Pixy.
	BlockSet blocks;

	std::string hexToStr(unsigned short int[], unsigned int);
	std::string hexToStr(std::vector<unsigned short int>);
	template< typename T > std::string intToHex(T);

	int getBlocks(int);
	int getWord();
	bool getStart();
	unsigned char getByte(unsigned char);
	unsigned char send(unsigned char *, unsigned char);
	void rawComms();
};

#endif  // EXAMPLE_SUBSYSTEM_H
