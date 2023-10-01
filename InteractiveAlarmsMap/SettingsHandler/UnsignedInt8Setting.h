#ifndef UnsignedInt8Setting_h
#define UnsignedInt8Setting_h
#pragma once

#include "../Libraries/Streaming/Streaming.h"

#include <EEPROM.h>

//	EEPROM must be initialized externaly.
//  Serial should be initialized externaly.

class UnsignedInt8Setting
{
    private:
        
        uint16_t addressIndex = 0;
        uint8_t value = 0;

    public:

        UnsignedInt8Setting(uint16_t addressIndex)
        {
            this->addressIndex = addressIndex;
            updateFromMemory();
        }

        void setValue(uint8_t newValue)
        {
            EEPROM.put(addressIndex, newValue);

            Serial << "[Information] Saving unsigned int 8 setting to memory." << endl;

            EEPROM.commit();
            updateFromMemory();
        }

        uint8_t getValue()
        {
            return value;
        }

    private:

        void updateFromMemory()
        {
            EEPROM.get(addressIndex, value);
        }
      
};

#endif
