#include "PixySPI.h"
#include "../RobotMap.h"
#include "SmartDashboard/SmartDashboard.h"
#include <iomanip>

PixySPI::PixySPI(SPI::Port port) : Subsystem("PixySPI") {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
	pixy = new SPI(port);
	packets = new PacketMapSet;

	// Set some SPI parameters.
	pixy->SetMSBFirst();
	pixy->SetChipSelectActiveLow();
	pixy->SetClockRate(1000);
	pixy->SetSampleDataOnFalling();
	pixy->SetClockActiveLow();
}

//This method gathers data, then parses that data, and assigns the info to global variables
//The signature should be which number object in
int PixySPI::readPackets()  {
	if(debug >= 1) {SmartDashboard::PutNumber("readPackets: count: ", readPacketsCount++);}

	// Uncomment this to see just the raw output from the Pixy. You will need to restart the robot code
	// to kill this.
	//rawComms();

	int numBlocks = getBlocks(1000);

	// Clear out and initialize ArrayList for PixyPackets.
	packets->clear();

	for(int i=1; i<=PIXY_SIG_COUNT; i++) {
		packets->insert (PacketMapSet::value_type(i, PacketSet()));
	}

	// Put the found blocks into the correct spot in the return std::map<int, PacketSet> PacketMapSet
	if(numBlocks > 0) {
		if(debug >= 2) {std::cout << "Pixy readPackets: blocks detected: " << std::to_string(numBlocks) << std::endl;}
		if(debug >= 1) {SmartDashboard::PutString("Pixy readPackets: blocks detected: ", std::to_string(numBlocks));}

		for (std::vector<std::vector<unsigned short int> >::iterator it = blocks.begin(); it != blocks.end(); it++) {
			// Create the PixyPacket for the current blocks.
			PixyPacket *packet = new PixyPacket;
			int signature = (int) (*it).at(0);
			packet->X = (*it).at(1);
			packet->Y = (*it).at(2);
			packet->Width = (*it).at(3);
			packet->Height = (*it).at(4);

			if(debug >= 1) {SmartDashboard::PutString("Pixy readPackets: Signature: " + std::to_string(signature), std::to_string(signature));}
			if(debug >= 1) {SmartDashboard::PutString("Pixy readPackets: " + std::to_string(signature) + ": X: ", std::to_string(packet->X));}
			if(debug >= 1) {SmartDashboard::PutString("Pixy readPackets: " + std::to_string(signature) + ": Y: ", std::to_string(packet->Y));}
			if(debug >= 1) {SmartDashboard::PutString("Pixy readPackets: " + std::to_string(signature) + ": Width: ", std::to_string(packet->Width));}
			if(debug >= 1) {SmartDashboard::PutString("Pixy readPackets: " + std::to_string(signature) + ": Height: ", std::to_string(packet->Height));}
			if(debug >= 2) {std::cout << "Pixy readPackets: Signature: " + std::to_string(signature), std::to_string(signature);}
			if(debug >= 2) {std::cout << "Pixy readPackets: " << std::to_string(signature) << ": X: " << std::to_string(packet->X);}
			if(debug >= 2) {std::cout << "Pixy readPackets: " << std::to_string(signature) << ": Y: " << std::to_string(packet->Y);}
			if(debug >= 2) {std::cout << "Pixy readPackets: " << std::to_string(signature) << ": Width: " << std::to_string(packet->Width);}
			if(debug >= 2) {std::cout << "Pixy readPackets: " << std::to_string(signature) << ": Height: " << std::to_string(packet->Height);}

			// Add the current PixyPacket to the correct location for the signature.
			packets->at(signature).push_back(*packet);
			if(debug >= 1) {SmartDashboard::PutString("Pixy readPackets: packets size: ", std::to_string(packets->at(signature).size()));}
		}
	}

	return(1);
}

int PixySPI::getBlocks(int maxBlocks) {
	// Clear out blocks array list for reuse.
	blocks.clear();
	long count = 0;

	if(debug >= 1) {SmartDashboard::PutString("getBlock: count: ", std::to_string(++getBlockCount));}

	// If we haven't found the start of a block, find it.
	if(! skipStart) {
		// If we can't find the start of a block, drop out.
		if(! getStart()) {
			return(0);
		}
	}
	else {
		// Clear flag that tells us to find the next block as the logic below will loop
		// the appropriate number of times to retrieve a complete block.
		skipStart = false;
	}

	// Loop until we hit the maximum size allowed for blocks, or until we know we have a complete set of blocks.
	while ((blocks.size()) < maxBlocks && (blocks.size() < PIXY_MAXIMUM_ARRAYSIZE)) {
		if(debug >= 1) {SmartDashboard::PutString("getBlocks: loop count: ", std::to_string(++count));}

		// Since this is our first time in, bytes 2 and 3 are the checksum, grab them and store for future use.
		// NOTE: getWord grabs the entire 16 bits in one shot.
		int checksum = getWord();
		int trialsum = 0;

		// See if the checksum is really the beginning of the next block,
		// in which case return the current set of blocks found and set the flag
		// to skip looking for the beginning of the next block since we already found it.
		if(checksum == PIXY_START_WORD) {
			if(debug >= 2) {std::cout << "Pixy: getBlocks: checksum == PIXY_START_WORD" << std::endl;}
			skipStart = true;
			return(blocks.size());
		}
		// See if we received a empty buffer, if so, assume end of comms for now and return what we have.
		else if (checksum == 0) {
			if(debug >= 2) {std::cout << "Pixy: getBlocks: checksum == 0" << std::endl;}
			return(blocks.size());
		}

		// Start building the block which will be stored in the overall set of blocks.
		// Only need 5 slots since the first 3 slots, the double start blocks and checksum, have been retrieved already.
		std::vector<unsigned short int> block (5,0);
		for(int i=0; i<BLOCK_LEN; i++) {
			block.insert(block.begin() + i, getWord());
			trialsum += block.at(i);
			// intsToHex doesn't work yet. Unable to test and fix at the moment.
			// It will show up in the log and SmartDashboard with no data.
			// That does NOT inherently mean anything is wrong with core code.
			if(debug >= 2) {std::cout << "Pixy: getBlocks: block: " << hexToStr(block);}
			if(debug >= 1) {SmartDashboard::PutString("Pixy: getBlocks: block: ", hexToStr(block));}
		}

		if(debug >= 2) {std::cout << "Pixy: getBlocks checksum: " << intToHex(checksum);}
		if(debug >= 1) {SmartDashboard::PutString("Pixy: getBlocks checksum: ", intToHex(checksum));}
		if(debug >= 2) {std::cout << "Pixy: getBlocks trialsum: " << intToHex(trialsum);}
		if(debug >= 1) {SmartDashboard::PutString("Pixy: getBlocks trialsum: ", intToHex(trialsum));}

		// See if we received the data correctly.
		if(checksum == trialsum) {
			// Data has been validated, add the current block of data to the overall blocks buffer.
			blocks.push_back(block);
			if(debug >= 2) {std::cout << "Pixy: getBlocks Checksum: passed";}
			if(debug >= 1) {SmartDashboard::PutString("Pixy: getBlocks Checksum", "passed");}
		}
		else {
			if(debug >= 2) {std::cout << "Pixy: getBlocks Checksum: failed";}
			if(debug >= 1) {SmartDashboard::PutString("Pixy: getBlocks Checksum", "failed");}
		}

		// Check the next word from the Pixy to confirm it's the start of the next block.
		// Pixy sends two aa55 words at start of block, this should pull the first one.
		// The top of the loop should pull the other one.
		int w = getWord();

		if(debug >= 1) {SmartDashboard::PutString("Pixy: getBlocks: w: ", intToHex(w));}
		if(debug >= 2) {std::cout << "Pixy: getBlocks: w: " << intToHex(w);}

		if (w != PIXY_START_WORD) {
			if(debug >= 2) {std::cout << "Pixy: getBlocks: w != PIXY_START_WORD";}
			return(blocks.size());
		}
	}

	// Should never get here, but if we happen to get a massive number of blocks
	// and exceed the limit it will happen. In that case something is wrong
	// or you have a super natural Pixy and SPI link.
	return(0);
}

// Pixy SPI comm functions derived from https://github.com/omwah/pixy_rpi
int PixySPI::getWord() {
	unsigned short int w;
	unsigned char c, out = 0;

	if(debug >= 1) {SmartDashboard::PutString("getWord: count: ", std::to_string(++getWordCount));}

	if (outBuf.size() > 0) {
		// Add Vector output buffer code here.
		w = getByte(PIXY_SYNC_BYTE_DATA);
		out = outBuf.front();
		outBuf.pop();
	}
	else {
		// This is where we getByte.
		w = getByte(PIXY_SYNC_BYTE);
	}

	// Store the value of the buffer to a string for debugging to the console/log and SmartDashboard.
	if(debug >= 1) {SmartDashboard::PutString("Pixy: getWord: write sync: ", intToHex(out));}
	if(debug >= 2) {std::cout << "Pixy: getWord: write sync: " << intToHex(out);}

	// Store the contents of the buffer in a int that will be returned to the caller.
	w <<= 8;
	c = getByte(out);
	w |= c;

	//Store the value of the buffer to a string for debugging to the console/log and SmartDashboard
	if(debug >= 1) {SmartDashboard::PutString("Pixy: getWord: read sync: ", intToHex(w));}
	if(debug >= 2) {std::cout << "Pixy: getWord: read sync: " << intToHex(w);}

	if(debug >= 1) {SmartDashboard::PutString("Pixy: getWord: word: ", intToHex(w));}

	// Clear the buffers, not needed, but nice to know they are cleaned out.
	return(w);
}

unsigned char PixySPI::getByte(unsigned char out=0x00) {
	unsigned char ret = 0;

	// Send the sync / data bit / 0 to get the Pixy to return data appropriately.
	pixy->Transaction(&out, &ret, 1);
	return ret;
}

// Need to come back to this one, used only for send control data to Pixy.
unsigned char PixySPI::send(unsigned char *data, unsigned char len) {
	if (len > PIXY_OUTBUF_SIZE || outBuf.size() != 0) {
		return -1;
	}

	outBuf.push(*data);
	return outBuf.size();
}

bool PixySPI::getStart() {
	int lastw = 0xff;
	int count=0;

	if(debug >= 1) {SmartDashboard::PutString("getStart: count: ", std::to_string(++getStartCount));}

	// Loop until we get a start word from the Pixy.
	while(true) {
		int w = getWord();
		if(debug >= 2) {std::cout <<  "Pixy: getStart: w: ", intToHex(w);}
		if(debug >= 1) {
			SmartDashboard::PutString("Pixy: getStart: w: ", intToHex(w));
			SmartDashboard::PutNumber("getStart: loop count: ", count++);
		}
		if ((w == 0x00) && (lastw == 0x00)) {
			// Could delay a bit to give time for next data block, but to get accurate time would tie up cpu.
			// So might as well return and let caller call this getStart again.
			if(debug >= 2) {std::cout << "Pixy: getStart: no pixy data received";}
			if(debug >= 1) {SmartDashboard::PutString("Pixy: getStart: ", "no pixy data received");}
			return(false);
		}
		else if (((int) w == PIXY_START_WORD) && ((int) lastw == PIXY_START_WORD)) {
			if(debug >= 2) {std::cout << "Pixy: getStart: found start";}
			if(debug >= 1) {SmartDashboard::PutString("Pixy: getStart: ", "found start");}
			return(true);
		}
		else if (w == PIXY_START_WORDX) {
			if(debug >= 2) {std::cout << "Pixy: getStart: reorder" << std::endl;}
			if(debug >= 1) {SmartDashboard::PutString("Pixy: getStart: ", "reorder");}
			getByte(); // resync
		}

		lastw = w;
	}
}

// Some debugging functions and assorted trinkets.
// Derived from http://stackoverflow.com/questions/10723403/char-array-to-hex-string-c
std::string PixySPI::hexToStr(unsigned short int data[], unsigned int data_length) {
	std::stringstream ss;
	for(int i=0; i<data_length; i++) {
		ss << std::hex << (int)data[i];
	}
	return(ss.str());
}

std::string PixySPI::hexToStr(std::vector<unsigned short int> data) {
	std::stringstream ss;
	for(std::vector<unsigned short int>::iterator it = data.begin(); it != data.end(); ++it) {
		ss << std::hex << (int) *it;
	}
	return(ss.str());
}

// Derived from http://stackoverflow.com/questions/5100718/integer-to-hex-string-in-c
template< typename T >
std::string PixySPI::intToHex(T i) {
	std::stringstream stream;
	stream << std::setfill ('0') << std::setw(sizeof(T)*2) << std::hex << i;
	return(stream.str());
}

// Call this from readPackets, it's there commented out already.
// Read the warning there as well.
// This will dump all data to the console/log and SmartDashboard
// Set the debug level accordingly, otherwise it's going to be a bit boring
// watching nothing happen while your RoboRio is screaming into the void.
void PixySPI::rawComms() {
	unsigned char out (PIXY_SYNC_BYTE);
	unsigned char ret = 0;

	while (true) {
		if(debug >= 2) {std::cout << "Pixy: rawComms: write sync: " << intToHex(out);}
		if(debug >= 1) {SmartDashboard::PutString("Pixy: rawComms: write sync: ", intToHex(out));}

		// Send the sync / data bit / 0 to get the Pixy to return data appropriately.
		pixy->Transaction(&out, &ret, 1);

		if(debug >= 2) {std::cout << "Pixy: rawComms: read sync: ", intToHex(ret);}
		if(debug >= 1) {SmartDashboard::PutString("Pixy: rawComms: read sync: ", intToHex(ret));}
	}
}

