#ifndef ModeSetting_h
#define ModeSetting_h
#pragma once

#include <EEPROM.h>

//	EEPROM must be initialized externaly.

class ModeSetting
{
    private:
        
        int addressIndex;
        uint8_t value;

    public:

        ModeSetting()
        {
            addressIndex = 0;
            updateValueFromMemory();
        }

        void setValue(uint8_t newValue)
        {
            EEPROM.put(addressIndex, newValue);
            EEPROM.commit();
            updateValueFromMemory();
        }

        uint8_t getValue()
        {
            return value;
        }

    private:

        void updateValueFromMemory()
        {
            EEPROM.get(addressIndex, value);
        }
      
};

#endif
