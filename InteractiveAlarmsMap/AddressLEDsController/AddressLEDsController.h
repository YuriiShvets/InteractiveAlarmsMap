#ifndef AddressLEDsController_h
#define AddressLEDsController_h
#pragma once

#include <Adafruit_NeoPixel.h>
#include "AddressLED.h"

class AddressLEDsController
{
	private:
		
		uint16_t numberOfLEDs = 0;
		Adafruit_NeoPixel* LEDsControl = NULL;
		AddressLED** addressLEDs = NULL;
		bool colorsAreUpToDate = false;


	public:

		AddressLEDsController(uint16_t numberOfLEDs, int16_t controlPin)
		{
			this->numberOfLEDs = numberOfLEDs;
			LEDsControl = new Adafruit_NeoPixel(numberOfLEDs, controlPin, NEO_GRB + NEO_KHZ800);
			LEDsControl->begin();

			addressLEDs = new AddressLED * [numberOfLEDs];
			for (uint16_t i = 0; i < numberOfLEDs; i++)
			{
				addressLEDs[i] = new AddressLED();
			}
		}

		// Updates each LED color to required value instantly.
		void Update()
		{
			for (uint16_t i = 0; i < numberOfLEDs; i++)
			{
				LEDsControl->setPixelColor(i, addressLEDs[i]->getRedColorValue(), addressLEDs[i]->getGreenColorValue(), addressLEDs[i]->getBluColorValue());
			}

			LEDsControl->show();

			colorsAreUpToDate = true;
		}

		// Updates each LED color to required value by one step at a time.
		void smoothUpdate()
		{
			colorsAreUpToDate = true;

			for (uint16_t i = 0; i < numberOfLEDs; i++)
			{
				uint8_t currentRedColorValue = LEDsControl->getPixelColor(i) >> 16;
				uint8_t currentGreenColorValue = (LEDsControl->getPixelColor(i) << 16) >> 24;
				uint8_t currentBluColorValue = (LEDsControl->getPixelColor(i) << 24) >> 24;

				uint8_t newRedColorValue = currentRedColorValue;
				uint8_t newGreenColorValue = currentGreenColorValue;
				uint8_t newBluColorValue = currentBluColorValue;
				
				if (currentRedColorValue < addressLEDs[i]->getRedColorValue())
				{
					newRedColorValue++;
					colorsAreUpToDate = false;
				}
				else if (currentRedColorValue > addressLEDs[i]->getRedColorValue())
				{
					newRedColorValue--;
					colorsAreUpToDate = false;
				}

				if (currentGreenColorValue < addressLEDs[i]->getGreenColorValue())
				{
					newGreenColorValue++;
					colorsAreUpToDate = false;
				}
				else if (currentGreenColorValue > addressLEDs[i]->getGreenColorValue())
				{
					newGreenColorValue--;
					colorsAreUpToDate = false;
				}

				if (currentBluColorValue < addressLEDs[i]->getBluColorValue())
				{
					newBluColorValue++;
					colorsAreUpToDate = false;
				}
				else if (currentBluColorValue > addressLEDs[i]->getBluColorValue())
				{
					newBluColorValue--;
					colorsAreUpToDate = false;
				}

				LEDsControl->setPixelColor(i, newRedColorValue, newGreenColorValue, newBluColorValue);
			}

			LEDsControl->show();
		}

		uint16_t getNumberOfLEDs()
		{
			return numberOfLEDs;
		}

		AddressLED** getLEDs()
		{
			return addressLEDs;
		}

		bool AreAllColorsUpToDate()
		{
			colorsAreUpToDate = true;

			for (uint16_t i = 0; i < numberOfLEDs; i++)
			{
				uint8_t currentRedColorValue = LEDsControl->getPixelColor(i) >> 16;
				uint8_t currentGreenColorValue = (LEDsControl->getPixelColor(i) << 16) >> 24;
				uint8_t currentBluColorValue = (LEDsControl->getPixelColor(i) << 24) >> 24;

				colorsAreUpToDate &= ((currentRedColorValue == addressLEDs[i]->getRedColorValue()) && (currentGreenColorValue == addressLEDs[i]->getGreenColorValue()) && (currentBluColorValue == addressLEDs[i]->getBluColorValue()));
			}

			return colorsAreUpToDate;
		}

		~AddressLEDsController()
		{
			delete LEDsControl;
			
			for (uint16_t i = 0; i < numberOfLEDs; i++)
			{
				delete addressLEDs[i];
			}
			delete addressLEDs;
		}
};

#endif
