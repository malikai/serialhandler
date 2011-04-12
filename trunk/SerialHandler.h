/*
This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

By : Madrang of The Warrent Team
*/

#ifndef SerialHandler_h
#define SerialHandler_h

#include <inttypes.h>
#include "Print.h"

/******************************************************************************
* Definitions
******************************************************************************/

class SerialHandler : public Print
{
#define ByteBufferLenght 16
#define FunctionBufferLenght 128
#define _SerialHandler_VERSION 5 // software version of this library
private:
	// per object data
	uint8_t BufferCount;
	uint8_t Buffer[ByteBufferLenght];

	uint8_t (*Avail)(void);
	void (*SerialSend)(uint8_t);
	int (*SerialRead)(void);
	typedef void (*H_voidFuncPtr)(uint8_t[]);
	H_voidFuncPtr intFunc[FunctionBufferLenght];
	H_voidFuncPtr ErrorFunc;

	// static data

	// private methods
	void ProcessCommand();
	void write(uint8_t);
	int read();
	uint8_t available(void);
	
public:
	// public methods
	SerialHandler(uint8_t(*)(), int(*)(), void(*)(uint8_t),H_voidFuncPtr);//(Serial.available,Serial.read,Serial.write)
	void Flush();
	bool GetSerial(uint8_t);
	void AttachFunction(void(*)(uint8_t[]),uint8_t);
	void DetachFunction(uint8_t);
	char Abord;
	char Ack;
	uint16_t WaitTime;
	int BufferLength(){return BufferCount;}
	uint8_t GetBuffer();
	static int library_version() { 
		return _SerialHandler_VERSION;} 
};

// Arduino 0012 workaround
#undef int
#undef char
#undef long
#undef byte
#undef float
#undef abs
#undef round 

#endif
