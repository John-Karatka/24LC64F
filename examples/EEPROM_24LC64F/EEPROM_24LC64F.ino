#include <EEPROM_24LC64F.h>
#include <Wire.h>

#define address 80    //address of chip
#define startAddress 0x0000 //Start address of write and read

EEPROM_24LC64F tmp(address);

void setup() {
  Serial.begin(9600);
}

void loop() {
  uint8_t startAddressHigh = 0;
  uint8_t startAddressLow = 0;
  uint8_t data[] = {'t', 'e', 's', 't', 'i', 'n', 'g'};
  int dataSize = (sizeof(data)/sizeof(data[0]));
  uint8_t buffer[dataSize];
  int readAmount = dataSize;
  
  tmp.writeMem(startAddress, data, dataSize);      //write to chip memory
  tmp.readMem(startAddress, readAmount, buffer);   //read data that was written
  
  for (int i = 0; i < readAmount; i++) {
    Serial.println(char(buffer[i]));                        //print data
  }
  delay(1000);
}
