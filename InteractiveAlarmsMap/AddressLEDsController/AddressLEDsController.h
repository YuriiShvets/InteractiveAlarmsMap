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

		void Update()
		{
			for (uint16_t i = 0; i < numberOfLEDs; i++)
			{
				LEDsControl->setPixelColor(i, addressLEDs[i]->getRedColorValue(), addressLEDs[i]->getGreenColorValue(), addressLEDs[i]->getBluColorValue());
				addressLEDs[i] = new AddressLED();
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
