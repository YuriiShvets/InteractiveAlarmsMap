#ifndef StringSetting_h
#define StringSetting_h
#pragma once

#include "../Libraries/Streaming/Streaming.h"

#include <EEPROM.h>
#include <stdexcept>

//	EEPROM must be initialized externaly.
//	Serial must be initialized externaly.

class StringSetting
{
	private:

		uint16_t addressIndex = 0;
		uint16_t maxSize = 0;
		uint16_t usedSize = 0;	//	Stored in first 2 bytes.
		String value = "";		//	Stored after 2 first bytes. Can not be longer that maxSize.

	public:

		StringSetting(uint16_t addressIndex, uint16_t maxSize)
		{
			this->addressIndex = addressIndex;
			this->maxSize = maxSize;
		}

		void setValue(String newValue)
		{
			if (newValue.length() > maxSize)
			{
				throw runtime_error("New value of String setting is longer than maximum setting size.");
			}

			// Writing used size to first 2 bytes.
			EEPROM.put(addressIndex, newValue.length() >> 8);
			EEPROM.put(addressIndex + 1, (newValue.length() << 8) >> 8);

			// Writing value.
			for (int i = 0; i < newValue.length(); i++)
			{
				EEPROM.put(addressIndex + 2 + i, newValue.charAt(i));
			}

			Serial << "[Information] Saving String setting to memory." << endl;

			EEPROM.commit();
			updateFromMemory();
		}

		String getValue()
		{
			return value;
		}

		uint16_t getAddress()
		{
			return addressIndex;
		}

		uint16_t getMaxSize()
		{
			return maxSize + 2;
		}

		void updateFromMemory()
		{
			// Reading of a used size from first 2 bytes.
			EEPROM.get(addressIndex, usedSize);
			usedSize = usedSize << 8;
			uint8_t secondHalfOfUsedSize = 0;
			EEPROM.get(addressIndex + 1, secondHalfOfUsedSize);
			usedSize |= secondHalfOfUsedSize;

			if (usedSize > maxSize)
			{
				usedSize = maxSize;
				Serial << "[Warning] Settings used space are bigger than maximum size of the setting." << endl;
			}

			// Reading of a value.
			value = "";
			for (int i = 0; i < usedSize; i++)
			{
				char character;
				EEPROM.get(addressIndex + 2 + i, character);
				value += character;
			}
		}
};

#endif
