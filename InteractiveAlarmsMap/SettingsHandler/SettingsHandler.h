#ifndef SettingsHandler_h
#define SettingsHandler_h
#pragma once

#include "ModeSetting.h"
#include <EEPROM.h>

//	Serial must be initialized externaly.

class SettingsHandler
{

    private:
        ModeSetting* modeSetting;

    public:

        SettingsHandler()
        {
            int numberOfUsedBytes = 1;

            EEPROM.begin(numberOfUsedBytes);

            modeSetting = new ModeSetting();

            Serial.println("Handler of settings was initialized.");
        }

        void setMode(uint8_t newMode)
        {
            modeSetting->setValue(newMode);
        }

        uint8_t getMode()
        {
            return modeSetting->getValue();
        }

        ~SettingsHandler()
        {
            delete modeSetting;
        }
      
};

#endif
