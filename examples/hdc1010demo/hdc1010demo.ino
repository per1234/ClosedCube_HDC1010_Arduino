/**************************************************************************************

This is example for ClosedCube HDC1010 Humidity and Temperature Sensor breakout booard

Initial Date: 20-Oct-2016

Hardware connections for Arduino Uno:
	VDD to 3.3V DC
	SCL to A5
	SDA to A4
	GND to common ground

Written by AA for ClosedCube

MIT License

**************************************************************************************/

#include <Wire.h>
#include "ClosedCube_HDC1010.h"

ClosedCube_HDC1010 hdc1010;

void setup()
{
	Serial.begin(9600);
	Serial.println("ClosedCube HDC1010 Arduino Test");

	hdc1080.begin(0x40);

	Serial.print("Manufacturer ID=0x");
	Serial.println(hdc1010.readManufacturerId(), HEX); // 0x5449 ID of Texas Instruments
	Serial.print("Device ID=0x");
	Serial.println(hdc1010.readDeviceId(), HEX); // 0x1000 ID of the device
	
}

void loop()
{
	Serial.print("T=");
	Serial.print(hdc1010.readTemperature());
	Serial.print("C, RH=");
	Serial.print(hdc1010.readHumidity());
	Serial.println("%");
	delay(300);
}

