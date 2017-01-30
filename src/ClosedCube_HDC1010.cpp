/*

Arduino Library for Texas Instruments HDC1010 Digital Humidity and Temperature Sensor
Written by AA for ClosedCube
---

The MIT License (MIT)

Copyright (c) 2016 ClosedCube Limited

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

#include <Wire.h>

#include "ClosedCube_HDC1010.h"


ClosedCube_HDC1010::ClosedCube_HDC1010()
{
}

void ClosedCube_HDC1010::begin(uint8_t address) {
	_address = address;
	Wire.begin();

	Wire.beginTransmission(_address);
	Wire.write(CONFIGURATION);
	Wire.write(0x0);
	Wire.write(0x0);
	Wire.endTransmission();

}

void ClosedCube_HDC1010::setHeaterOn() {
	HDC1010_Registers reg = readRegister();
	reg.Heater = 1;
	writeRegister(reg);
}

void ClosedCube_HDC1010::setHeaterOff() {
	HDC1010_Registers reg = readRegister();
	reg.Heater = 0;
	writeRegister(reg);
}

float ClosedCube_HDC1010::readT() {
	return readTemperature();
}

float ClosedCube_HDC1010::readTemperature() {
	uint16_t rawT = readData(TEMPERATURE);
	return (rawT / pow16) * 165 - 40;
}

float ClosedCube_HDC1010::readH() {
	return readHumidity();
}

float ClosedCube_HDC1010::readHumidity() {
	uint16_t rawH = readData(HUMIDITY);
	return (rawH / pow16) * 100;
}

uint16_t ClosedCube_HDC1010::readManufacturerId() {
	return readData(MANUFACTURER_ID);
}

HDC1010_Registers ClosedCube_HDC1010::readRegister() {
	HDC1010_Registers reg;
	reg.rawData = (readData(CONFIGURATION) >> 8);
	return reg;
}

void ClosedCube_HDC1010::writeRegister(HDC1010_Registers reg) {
	Wire.beginTransmission(_address);
	Wire.write(CONFIGURATION);
	Wire.write(reg.rawData);
	Wire.write(0x00);
	Wire.endTransmission();
}

uint16_t ClosedCube_HDC1010::readDeviceId() {
	return readData(DEVICE_ID);
}

uint16_t ClosedCube_HDC1010::readData(uint8_t pointer) {
	Wire.beginTransmission(_address);
	Wire.write(pointer);
	Wire.endTransmission();

	delay(10);
	Wire.requestFrom(_address, (uint8_t)2);

	byte msb = Wire.read();
	byte lsb = Wire.read();

	return msb << 8 | lsb;
}



