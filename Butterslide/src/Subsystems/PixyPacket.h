/*
 * PixyPacket.h
 *
 *  Created on: Feb 24, 2017
 *      Author: chris
 */

#ifndef SRC_SUBSYSTEMS_PIXYPACKET_H_
#define SRC_SUBSYSTEMS_PIXYPACKET_H_

 #include <stdint.h>

class PixyPacket {
public:
	unsigned short int X;
	unsigned short int Y;
	unsigned short int Width;
	unsigned short int Height;
	unsigned short int checksumError;

	PixyPacket();
	virtual ~PixyPacket();
};

#endif /* SRC_SUBSYSTEMS_PIXYPACKET_H_ */
