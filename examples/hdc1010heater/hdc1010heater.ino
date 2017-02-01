/**************************************************************************************

This is a heater example for ClosedCube HDC1010 Humidity and Temperature Sensor breakout booard

Initial Date: 01-Feb-2017

Hardware connections for Arduino Uno:
VDD to 3.3V DC
SCL to A5
SDA to A4
GND to common ground

Written by AA for ClosedCube

MIT License

**************************************************************************************/

#include "ClosedCube_HDC1010.h"
#include <Wire.h>

ClosedCube_HDC1010 hdc1010;

void setup()
{
	Serial.begin(9600);
	Serial.println("ClosedCube HDC1010 [Heater] Arduino Test");

	hdc1010.begin(0x41);

	Serial.print("Manufacturer ID=0x");
	Serial.println(hdc1010.readManufacturerId(), HEX); // 0x5449 ID of Texas Instruments
	Serial.print("Device ID=0x");
	Serial.println(hdc1010.readDeviceId(), HEX); // 0x1000 ID of the device
	
	Serial.println();

	HDC1010_Registers reg = hdc1010.readRegister();
	printRegister(reg);

	// @TODO: Heater config setup
}

void loop()
{
}

void printRegister(HDC1010_Registers reg) {
	Serial.println("HDC1010 Configuration Register");
	Serial.println("------------------------------");
	
	Serial.print("Software reset bit: ");
	Serial.print(reg.SoftwareReeset, BIN);
	Serial.println(" (0=Normal Operation, 1=Software Reset)");

	Serial.print("Heater: ");
	Serial.print(reg.Heater, BIN);
	Serial.println(" (0=Disabled, 1=Enabled)");

	Serial.print("Mode of Acquisition: ");
	Serial.print(reg.ModeOfAcquisition, BIN);
	Serial.println(" (0=T or RH is acquired, 1=T and RH are acquired in sequence, T first)");

	Serial.print("Battery Status: ");
	Serial.print(reg.BatteryStatus, BIN);
	Serial.println(" (0=Battery voltage > 2.8V, 1=Battery voltage < 2.8V)");

	Serial.print("T Measurement Resolution: ");
	Serial.print(reg.TemperatureMeasurementResolution, BIN);
	Serial.println(" (0=14 bit, 1=11 bit)");

	Serial.print("RH Measurement Resolution: ");
	Serial.print(reg.HumidityMeasurementResolution, BIN);
	Serial.println(" (00=14 bit, 01=11 bit, 10=8 bit)");
}
