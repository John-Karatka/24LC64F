/*
 * EEPROM_24LC64F - library for EEPROM_24LC64F EEPROM
 * This library is intended to be used with Aruino and the Arduino Wire library functions
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

#ifndef EEPROM_24LC64F_H
#define EEPROM_24LC64F_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <stdint.h>

class EEPROM_24LC64F {
private:
	unsigned char address;
	void busyCheck();

public:
	EEPROM_24LC64F(int EEPROM_Address);
	void writeMem(uint16_t startAddress, uint8_t *data, int dataSize);
	void readMem(uint16_t startAddress, int readAmount, uint8_t *buffer);
};

#endif
