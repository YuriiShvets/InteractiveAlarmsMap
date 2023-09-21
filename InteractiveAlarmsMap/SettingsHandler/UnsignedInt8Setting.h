#ifndef UnsignedInt8Setting_h
#define UnsignedInt8Setting_h
#pragma once

#include <EEPROM.h>

//	EEPROM must be initialized externaly.

class UnsignedInt8Setting
{
    private:
        
        int addressIndex = 0;
        uint8_t value = 0;

    public:

        UnsignedInt8Setting()
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
