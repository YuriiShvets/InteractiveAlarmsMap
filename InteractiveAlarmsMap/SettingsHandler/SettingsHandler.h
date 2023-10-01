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

        UnsignedInt8Setting* modeSetting = NULL;

        StringSetting* WiFiNettworkName = NULL;
        StringSetting* WiFiNettworkPassword = NULL;

        const string WiFiNetworkNameForbiddenCharacters = "?\"$[\\]+";
        const string WiFiNetworkNameForbiddenStartCharacters = "!#;";
        

    public:

        SettingsHandler()
        {
            modeSetting = new UnsignedInt8Setting(0);
            WiFiNettworkName = new StringSetting(modeSetting->getAddress() + modeSetting->getSize(), maxWiFiNetworkNameLength);
            WiFiNettworkPassword = new StringSetting(WiFiNettworkName->getAddress() + WiFiNettworkName->getMaxSize(), maxWiFiNetworkPasswordLength);

            EEPROM.begin(modeSetting->getSize() + WiFiNettworkName->getMaxSize() + WiFiNettworkPassword->getMaxSize());

            modeSetting->updateFromMemory();
            WiFiNettworkName->updateFromMemory();
            WiFiNettworkPassword->updateFromMemory();

        }

        //  -------------------- Mode settings --------------------

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

        //  -------------------- Wi-Fi network name settings --------------------

        const uint8_t minWiFiNetworkNameLength = 2;
        const uint8_t maxWiFiNetworkNameLength = 32;

        string getWiFiNetworkNameForbiddenCharacters()
        {
            return WiFiNetworkNameForbiddenCharacters;
        }

        string getWiFiNetworkNameForbiddenStartCharacters()
        {
            return WiFiNetworkNameForbiddenStartCharacters;
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

            for (char forbiddenCharacter : WiFiNetworkNameForbiddenCharacters)
            {
                if (newWiFiNetworkName.indexOf(forbiddenCharacter) != -1)
                {
                    throw runtime_error(WiFiNetworkNameForbiddenCharacters + " characters are forbidden for use in Wi-Fi network name.");
                }
            }

            for (char forbiddenStartCharacter : WiFiNetworkNameForbiddenStartCharacters)
            {
                if (newWiFiNetworkName.indexOf(forbiddenStartCharacter) == 0)
                {
                    throw runtime_error(WiFiNetworkNameForbiddenStartCharacters + " characters are forbidden for use at start of the Wi-Fi network name.");
                }
            }

            WiFiNettworkName->setValue(newWiFiNetworkName);
        }

        String getWiFiNetworkName()
        {
            return WiFiNettworkName->getValue();
        }

        //  -------------------- Wi-Fi network password settings --------------------

        const uint8_t minWiFiNetworkPasswordLength = 8;
        const uint8_t maxWiFiNetworkPasswordLength = 63;

        void setWiFiNetworkPassword(String newWiFiNetworkPassword)
        {
            if (newWiFiNetworkPassword.length() < minWiFiNetworkPasswordLength)
            {
                throw runtime_error(string("The Wi-Fi network password cannot contain less than ") + to_string(minWiFiNetworkPasswordLength) + " characters.");
            }
            if (newWiFiNetworkPassword.length() > maxWiFiNetworkPasswordLength)
            {
                throw runtime_error(string("The Wi-Fi network password cannot contain more than ") + to_string(maxWiFiNetworkPasswordLength) + " characters.");
            }

            WiFiNettworkPassword->setValue(newWiFiNetworkPassword);
        }

        String getWiFiNetworkPassword()
        {
            return WiFiNettworkPassword->getValue();
        }

        // -------------------------------------------------------------------------

        ~SettingsHandler()
        {
            delete modeSetting;
        }
      
};

#endif
