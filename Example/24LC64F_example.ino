#include <24LC64F.h>
#include <Wire.h>

#define address 0		//address of chip

24LC64F tmp(address);

void setup() {
    Wire.begin();
    Serial.begin(9600);
}

void loop() {
  int startAddressHigh = 0;
  int startAddressLow = 0;
  int readAmount = 4;
  int buffer[4];
  int data[4] = {'T', 'e', 's', 't'};
  
  tmp.writeMem(startAddressHigh, startAddressLow, data);					//write to chip memory
  tmp.readMem(startAddressHigh, startAddressLow, readAmount, buffer);		//read data that was written
  
  for (int i = 0; i < readAmount; i++) {
    Serial.print(buffer[i]);												//print data
  }
}
