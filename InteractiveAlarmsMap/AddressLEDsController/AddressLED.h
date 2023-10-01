#ifndef AddressLED_h
#define AddressLED_h
#pragma once

#include <Adafruit_NeoPixel.h>

class AddressLED
{
	private:

		uint8_t redColorValue = 0;
		uint8_t greenColorValue = 0;
		uint8_t blueColorValue = 0;

	public:

		void setRedColorValue(uint8_t redColorValue)
		{
			this->redColorValue = redColorValue;
		}

		uint8_t getRedColorValue()
		{
			return redColorValue;
		}


		void setGreenColorValue(uint8_t greenColorValue)
		{
			this->greenColorValue = greenColorValue;
		}

		uint8_t getGreenColorValue()
		{
			return greenColorValue;
		}


		void setBlueColorValue(uint8_t blueColorValue)
		{
			this->blueColorValue = blueColorValue;
		}

		uint8_t getBlueColorValue()
		{
			return blueColorValue;
		}
};

#endif

