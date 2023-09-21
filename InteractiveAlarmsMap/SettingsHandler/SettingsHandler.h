#ifndef SettingsHandler_h
#define SettingsHandler_h
#pragma once

#include "UnsignedInt8Setting.h"
#include <EEPROM.h>

//	Serial must be initialized externaly.

class SettingsHandler
{

    private:
        UnsignedInt8Setting* modeSetting = NULL;

    public:

        SettingsHandler()
        {
            int numberOfUsedBytes = 1;

            EEPROM.begin(numberOfUsedBytes);

            modeSetting = new UnsignedInt8Setting(0);
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
