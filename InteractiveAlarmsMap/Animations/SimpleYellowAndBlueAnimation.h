#ifndef SimpleYellowAndBlueAnimation_h
#define SimpleYellowAndBlueAnimation_h
#pragma once

#include "../AddressLEDsController/AddressLEDsController.h"

class SimpleYellowAndBlueAnimation
{
	private:

		unsigned long timeOfLastColorChange = 0;
		unsigned long colorChangePeriod = 0;  //  In milliseconds.
		uint32_t* iterations = NULL;	//	Holds current iteration for each LED.
		AddressLEDsController* addressLEDsController = NULL;

	public:

		SimpleYellowAndBlueAnimation(unsigned long colorChangePeriod, AddressLEDsController* addressLEDsController)
		{
			this->colorChangePeriod = colorChangePeriod;
			this->addressLEDsController = addressLEDsController;

			iterations = new uint32_t[addressLEDsController->getNumberOfLEDs()];
			for (uint16_t i = 0; i < addressLEDsController->getNumberOfLEDs(); i++)
			{
				iterations[i] = 1023 / addressLEDsController->getNumberOfLEDs() * i;
			}
		}

		void Update()
		{
            if (millis() - timeOfLastColorChange >= colorChangePeriod)
            {
                if (addressLEDsController->AreAllColorsUpToDate()) //  If all colors are up to date.
                { //  Set new colors.
                    for (uint16_t i = 0; i < addressLEDsController->getNumberOfLEDs(); i++)
                    {
                        if (iterations[i] < 256)    //  Yellow up.
                        {
                            addressLEDsController->getLEDs()[i]->setRedColorValue(iterations[i]);
                            addressLEDsController->getLEDs()[i]->setGreenColorValue(iterations[i]);
                            addressLEDsController->getLEDs()[i]->setBlueColorValue(0);
                        }
                        else if (iterations[i] < 512)   // Yellow down.
                        {
                            addressLEDsController->getLEDs()[i]->setRedColorValue(511 - iterations[i]);
                            addressLEDsController->getLEDs()[i]->setGreenColorValue(511 - iterations[i]);
                            addressLEDsController->getLEDs()[i]->setBlueColorValue(0);
                        }
                        else if ((iterations[i] < 768)) //  Blue up.
                        {
                            addressLEDsController->getLEDs()[i]->setRedColorValue(0);
                            addressLEDsController->getLEDs()[i]->setGreenColorValue(0);
                            addressLEDsController->getLEDs()[i]->setBlueColorValue(iterations[i] - 512);
                        }
                        else if ((iterations[i] < 1024))    // Blue down.
                        {
                            addressLEDsController->getLEDs()[i]->setRedColorValue(0);
                            addressLEDsController->getLEDs()[i]->setGreenColorValue(0);
                            addressLEDsController->getLEDs()[i]->setBlueColorValue(1023 - iterations[i]);
                        }
                        iterations[i]++;
                        if (iterations[i] >= 1024)
                        {
                            iterations[i] = 0;
                        }
                    }
                }
                addressLEDsController->smoothUpdate();
                timeOfLastColorChange = millis();
            }
		}
};

#endif

