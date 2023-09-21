#ifndef AddressLED_h
#define AddressLED_h
#pragma once

#include <Adafruit_NeoPixel.h>

class AddressLED
{
	private:

		uint8_t redColorValue = 0;
		uint8_t greenColorValue = 0;
		uint8_t bluColorValue = 0;

	public:

		void setRedColorValue(uint8_t newRedColorValue)
		{
			redColorValue = newRedColorValue;
		}

		uint8_t getRedColorValue()
		{
			return redColorValue;
		}


		void setGreenColorValue(uint8_t newGreenColorValue)
		{
			greenColorValue = newGreenColorValue;
		}

		uint8_t getGreenColorValue()
		{
			return greenColorValue;
		}


		void setBluColorValue(uint8_t newBluColorValue)
		{
			bluColorValue = newBluColorValue;
		}

		uint8_t getBluColorValue()
		{
			return bluColorValue;
		}
};

#endif

