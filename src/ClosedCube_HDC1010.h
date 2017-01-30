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

#ifndef _CLOSEDCUBE_HDC1010_h

#define _CLOSEDCUBE_HDC1010_h
#include <Arduino.h>

typedef enum {
	TEMPERATURE = 0x00,
	HUMIDITY = 0x01,
	CONFIGURATION = 0x02,
	MANUFACTURER_ID = 0xFE,
	DEVICE_ID = 0xFF,
	SERIAL_ID_FIRST = 0xFB,
	SERIAL_ID_MID = 0xFC,
	SERIAL_ID_LAST = 0xFD,
} HDC1010_Pointers;

typedef union {
	uint8_t rawData;
	struct {
		uint8_t SoftwareReeset : 1;
		uint8_t ReservedAgain : 1;
		uint8_t Heater : 1;
		uint8_t ModeOfAcquisition : 1;
		uint8_t BatteryStatus : 1;
		uint8_t TemperatureMeasurementResolution : 1;
		uint8_t HumidityMeasurementResolution : 2;
	};
} HDC1010_Registers;


class ClosedCube_HDC1010 {
public:
	ClosedCube_HDC1010();

	void begin(uint8_t address);
	uint16_t readManufacturerId(); // 0x5449 ID of Texas Instruments
	uint16_t readDeviceId(); // 0x1000 ID of the device

	HDC1010_Registers readRegister();	
	void writeRegister(HDC1010_Registers reg);

	void setHeaterOn();
	void setHeaterOff();

	float readTemperature();
	float readHumidity();

	float readT(); // short-cut for readTemperature
	float readH(); // short-cut for readHumidity

private:
	uint8_t _address;
	uint16_t readData(uint8_t pointer);

	const double pow16 = pow(2, 16);
};

#endif

