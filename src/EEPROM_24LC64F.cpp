/*
 * EEPROM_24LC64F - library for EEPROM_24LC64F EEPROM
 * This library is intended to be used with Arduino and the Aruino Wire library functions
 *
 * Version 1.0.0
 * Last updated - 12/8/21
 * John Karatka
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * Please send any questions or concerns to
 * john.karatka@gmail.com
 *
 ************************************************************************
 *
 * Wiring diagram for EEPROM chip EEPROM_24LC64F
 *
 *        ----
 *  1 A0-|    |-VCC 8
 *  2 A1-|    |-WP 7
 *  3 A2-|    |-SCL 6
 *  4  G-|    |-SDA 5
 *        ----
 */

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Wire.h>
#include "EEPROM_24LC64F.h"

//! Constructor
EEPROM_24LC64F::EEPROM_24LC64F(int EEPROM_Address) {
	address = EEPROM_Address;
	Wire.begin();
}

/*
 * @brief Checks if chip has finished writing data; requests until ACK or timeout
 * @retval None
 */
void EEPROM_24LC64F::busyCheck() {
	int counter = 0;
	int writeCheck;
	do {
		Wire.beginTransmission(address);

		#if ARDUINO >= 100
			Wire.write(0);
		#else
			Wire.send(0);
		#endif
		writeCheck = Wire.endTransmission();
		counter++;
		if (counter == 1000) {
			Serial.print("ERROR - NACK timout. Error = "); Serial.println(writeCheck);	//For error codes refer to https://www.arduino.cc/en/Reference/WireEndTransmission
			break;
		}
	} while(writeCheck != 0);
}

/*
 * @brief  Writes data to chip memory
 * @param  startAddressHigh: Start address high byte
 * @param  startAddressLow: Start address low byte
 * @param  data[]: Array of data that is to be written
 * @retval None
 */
void EEPROM_24LC64F::writeMem(int startAddressHigh, int startAddressLow, int data[], int dataSize) {
	if (dataSize > 32) {
		Serial.println("WARNING: Exeeded maximum page size. Maximum amount of bytes per page is 32");
	}
	dataSize = constrain(dataSize, 0, 32);	//the maximum data size that can be transferred at one time is 32 bytes
	
	Wire.beginTransmission(address);
	#if ARDUINO >= 100
		Wire.write(startAddressHigh);
		Wire.write(startAddressLow);
	#else
		Wire.send(startAddressHigh);
		Wire.send(startAddressLow);
	#endif
	for (int i = 0; i <= dataSize; i++) {
		#if ARDUINO >= 100
		Wire.write(data[i]);
		#else
		Wire.send(data[i]);
		#endif
	}
	Wire.endTransmission();
	busyCheck();
}

/*
 * @brief  Reads data from chip memory and places into buffer
 * @param  startAddressHigh: Start address high byte
 * @param  startAddressLow: Start address low byte
 * @param  readAmount: Amount of data to be read
 * @param  *buffer: Buffer array for read data to be placed into
 * @retval None
 */
void EEPROM_24LC64F::readMem(int startAddressHigh, int startAddressLow, int readAmount, char *buffer) {
	Wire.beginTransmission(address);
	#if ARDUINO >= 100
		Wire.write(startAddressHigh);
		Wire.write(startAddressLow);
	#else
		Wire.send(startAddressHigh);
		Wire.send(startAddressLow);
	#endif
	Wire.endTransmission(false);
	Wire.requestFrom(address, readAmount);
	for (int i = 0; i < readAmount; i++) {
		#if ARDUINO >= 100
			buffer[i] = Wire.read();
		#else
			buffer[i] = Wire.receive();
		#endif
	}
}
