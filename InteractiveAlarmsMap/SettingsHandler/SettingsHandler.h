#ifndef SettingsHandler_h
#define SettingsHandler_h
#pragma once

#include "UnsignedInt8Setting.h"
#include "StringSetting.h"

#include <EEPROM.h>
#include <stdexcept>

class SettingsHandler
{

    private:

        const uint8_t maxWiFiNetworkNameLength = 32;
        const uint8_t minWiFiNetworkNameLength = 2;
        //  TODO complete data formalization.

        UnsignedInt8Setting* modeSetting = NULL;
        StringSetting* WiFiNettworkName = NULL;
        

    public:

        SettingsHandler()
        {
            int numberOfUsedBytes = 35;

            EEPROM.begin(numberOfUsedBytes);

            modeSetting = new UnsignedInt8Setting(0);   //  1 byte.

            WiFiNettworkName = new StringSetting(1, maxWiFiNetworkNameLength);    //  34 bytes.
        }

        void setMode(uint8_t newMode)
        {
            if (newMode != 0 && newMode != 1)
            {
                throw runtime_error("Provided value is not supported. Supported values: 0, 1.");
            }

            modeSetting->setValue(newMode);
        }

        uint8_t getMode()
        {
            return modeSetting->getValue();
        }

        void setWiFiNetworkName(String newWiFiNetworkName)
        {
            if (newWiFiNetworkName.length() < minWiFiNetworkNameLength)
            {
                throw runtime_error(string("The Wi-Fi network name cannot contain less than ") + to_string(minWiFiNetworkNameLength) + " characters.");
            }
            if (newWiFiNetworkName.length() > maxWiFiNetworkNameLength)
            {
                throw runtime_error(string("The Wi-Fi network name cannot contain more than ") + to_string(maxWiFiNetworkNameLength) + " characters.");
            }

            string forbiddenCharacters = "?\"$[\\]+";

            for (char forbiddenCharacter : forbiddenCharacters)
            {
                if (newWiFiNetworkName.indexOf(forbiddenCharacter) != -1)
                {
                    throw runtime_error("?\"$[\\]+ characters are forbidden for use in Wi-Fi network name.");
                }
            }

            String forbiddenStartCharacters = "!#;";
            for (char forbiddenStartCharacter : forbiddenStartCharacters)
            {
                if (newWiFiNetworkName.indexOf(forbiddenStartCharacter) == 0)
                {
                    throw runtime_error("!#; characters are forbidden for use at start of the Wi-Fi network name.");
                }
            }

            WiFiNettworkName->setValue(newWiFiNetworkName);
        }

        String getWiFiNetworkName()
        {
            return WiFiNettworkName->getValue();
        }

        ~SettingsHandler()
        {
            delete modeSetting;
        }
      
};

#endif
