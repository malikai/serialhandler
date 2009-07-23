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

// Includes
#include "WConstants.h"
#include "SerialHandler.h"

// Private methods
void SerialHandler::ProcessCommand(){
	if(Buffer[0] < FunctionBufferLenght){
	void (*H_FuncPtr)(uint8_t[]) = intFunc[Buffer[0]];
	H_FuncPtr(Buffer);
	} else ErrorFunc(Buffer);
}

// public methods
SerialHandler::SerialHandler(uint8_t(*AV)(), int(*SR)(), void(*SS)(uint8_t),H_voidFuncPtr Err){//(Serial.available,Serial.Read,Serial.Write)
	WaitTime = 30;
	Avail = AV;
	SerialRead = SR;
	SerialSend = SS;
	Ack = 13;
	Abord = 27;
	ErrorFunc = Err;
	for(int a = 0;a < FunctionBufferLenght;a++){
		intFunc[a] = ErrorFunc;
	}
}
void SerialHandler::AttachFunction(void(*userfunction)(uint8_t[]),uint8_t Command){
	intFunc[Command] = userfunction;
}
void SerialHandler::DetachFunction(uint8_t Command){
	intFunc[Command] = ErrorFunc;
}

bool SerialHandler::GetSerial(uint8_t WaitForData){
	uint8_t LastByte;
	uint8_t ByteFound = 0;
	boolean timeout = false;
	while((WaitForData < ByteFound && !timeout) || (WaitForData == 0 && !timeout))
	{
		while(available() > 0)
		{
			LastByte = read();
			if(LastByte == Abord && WaitForData == 0){
				Flush();
			}
			else if(LastByte == Ack && WaitForData == 0){ //if we are waiting for them then we allready know what to do with them
				ProcessCommand();
				Flush();
			}
			else if(BufferCount < ByteBufferLenght){
				Buffer[BufferCount] = LastByte;
				BufferCount++;
				ByteFound++;
			}
			else return false;
		}
		if(available() <= 0 && !timeout){
			if(WaitTime > 0)delayMicroseconds(WaitTime);
			if(available() <= 0) timeout = true;
		}
	}
	return timeout;
}

uint8_t SerialHandler::GetBuffer(){
	uint8_t BufByte = Buffer[0];
	for(int a = 1;a < ByteBufferLenght;a++){
		Buffer[a-1] = Buffer[a];
	}
	if(BufferCount > 0){
	Buffer[BufferCount] = 0;
	BufferCount--;
	}
	return BufByte;
}

void SerialHandler::Flush(){
	for(uint8_t a=0; a < ByteBufferLenght; a++){
		Buffer[a] = 0;
	}
	BufferCount = 0;
}
void SerialHandler::write(uint8_t b){
	SerialSend(b);
}
uint8_t SerialHandler::available(void){
	return Avail();
}
int SerialHandler::read(){
	return SerialRead();
}
