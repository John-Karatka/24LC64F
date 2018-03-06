/*
 * 24LC64F - library for 2424LC64FF EEPROM
 * This library is intended to be used with Aruino and the Arduino Wire library functions
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

#ifndef 24LC64F_H
#define 24LC64F_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class 24LC64F {
private:
	int address;
	void busyCheck();

public:
	24LC64F(int EEPROM_Address);
	void writeMem(int startAddressHigh, int startAddressLow, int data[]);
	void readMem(int startAddressHigh, int startAddressLow, int readAmount, int *buffer);
};

#endif
