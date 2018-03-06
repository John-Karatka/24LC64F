/*
 * 24LC64F - library for 2424LC64FF EEPROM
 * This library is intended to be used with Arduino and the Aruino Wire library functions
 *
 * Version 1.0
 * Last updated - 5/9/17
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
 * Wiring diagram for EEPROM chip 2424LC64FF
 *
 *        ----
 *  1 A0-|    |-VCC 8
 *  2 A1-|    |-VCC 7
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
#include "24LC64F.h"

//! Constructor
24LC64F::24LC64F(int EEPROM_Address) {
	address = EEPROM_Address;
	Wire.begin();
}

/*
 * @brief Checks if chip has finished writing data; requests until ACK or timeout
 * @retval None
 */
void 24LC64F::busyCheck() {
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
void 24LC64F::writeMem(int startAddressHigh, int startAddressLow, int data[]) {
	int dataSize = sizeof(data);
	int sendCount = dataSize / 32;					//The chip can only accept 32 bytes of data per page
	int leftOver = dataSize - (sendCount * 32);		//Gets leftover amount of data
	int dataCount = 0;

	if ((sendCount == 0) && (dataSize > 0)) {		//If the total amount of send data is less than 32, send the data normally
		Wire.beginTransmission(address);

			#if ARDUINO >= 100
				Wire.write(startAddressHigh);
				Wire.write(startAddressLow);
			#else
				Wire.send(startAddressHigh);
				Wire.send(startAddressLow);
			#endif

		for (int i = 0; i < dataSize; i++) {

			#if ARDUINO >= 100
				Wire.write(data[i]);
			#else
				Wire.send(data[i]);
			#endif

		}
		Wire.endTransmission();
		busyCheck();
	}

	else {											//If the data is over 32, send multiple times because 32 bytes is the limit of each page write
		for (int j = 0; j < sendCount; j++) {
			Wire.beginTransmission(address);

			#if ARDUINO >= 100
				Wire.write(startAddressHigh);
				Wire.write(startAddressLow);
			#else
				Wire.send(startAddressHigh);
				Wire.send(startAddressLow);
			#endif

			for (int r = 0; r < 31; r++) {

				#if ARDUINO >= 100
					Wire.write(data[dataCount]);
				#else
					Wire.send(data[dataCount]);
				#endif

				dataCount++;
			}
			Wire.endTransmission();
			busyCheck();
		}
		if (leftOver > 0) {							//Any leftover data gets sent
			Wire.beginTransmission(address);

			#if ARDUINO >= 100
				Wire.write(startAddressHigh);
				Wire.write(startAddressLow);
			#else
				Wire.send(startAddressHigh);
				Wire.send(startAddressLow);
			#endif

			for (int k = 0; k < leftOver; k++) {

				#if ARDUINO >= 100
					Wire.write(data[dataCount]);
				#else
					Wire.send(data[dataCount]);
				#endif

				dataCount++;
			}
			Wire.endTransmission();
			busyCheck();
		}
	}
}

/*
 * @brief  Reads data from chip memory and places into buffer
 * @param  startAddressHigh: Start address high byte
 * @param  startAddressLow: Start address low byte
 * @param  readAmount: Amount of data to be read
 * @param  *buffer: Buffer array for read data to be placed into
 * @retval None
 */
void 24LC64F::readMem(int startAddressHigh, int startAddressLow, int readAmount, int *buffer) {
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
