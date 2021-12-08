#include <EEPROM_24LC64F.h>
#include <Wire.h>

#define address 80    //address of chip

EEPROM_24LC64F tmp(address);

void setup() {
  Serial.begin(9600);
}

void loop() {
  int startAddressHigh = 0;
  int startAddressLow = 0;
  int data[] = {'t', 'e', 's', 't', 'i', 'n', 'g'};
  int dataSize = (sizeof(data)/sizeof(data[0]));
  char buffer[dataSize];
  int readAmount = dataSize;
  
  tmp.writeMem(startAddressHigh, startAddressLow, data, dataSize);      //write to chip memory
  tmp.readMem(startAddressHigh, startAddressLow, readAmount, buffer);   //read data that was written
  
  for (int i = 0; i < readAmount; i++) {
    Serial.println(buffer[i]);                        //print data
  }
  delay(1000);
}