#ifndef SerialCommandsHandler_h
#define SerialCommandsHandler_h
#pragma once

#include "SerialCommand.h"
#include "../SettingsHandler/SettingsHandler.h"
#include "../Libraries/Streaming/Streaming.h"

#include <stdexcept>

using namespace std;

//	Handler of serial commands.
//	Serial must be initialized externaly.

class SerialCommandsHandler
{
    private:
        SettingsHandler* settings = NULL;

    public:
        SerialCommandsHandler(SettingsHandler* settings)
        {
            this->settings = settings;

            Serial << "Handler of serial commands was initialized. Use help command to view all commands." << endl;
        }

        void Update()
        {
            if (Serial.available())
            {
                String str = Serial.readString();

                Serial.print(" -> ");
                Serial.println(str);

                try
                {
                    SerialCommand command = parceCommand(str);

                    if (command.getName() == "help")
                    {
                        Serial << "help - shows list of all commands." << endl;
                        
                        Serial << "setMode <mode> (mode: 0 - standart mode; 1 - interactive alarms mode) - command for mode setting." << endl;
                        
                        Serial << "getMode - shows current work mode." << endl;
                        
                        Serial << "setWiFiNetworkName <WiFiNetworkName> - command for setting of Wi-Fi network name." << endl;
                        Serial << "  Wi-Fi network can be any alphanumeric, case-sensitive entry from " << settings->minWiFiNetworkNameLength
                            << " to " << settings->maxWiFiNetworkNameLength << " characters." << endl;
                        Serial << "  Not allowed characters: " << settings->getWiFiNetworkNameForbiddenCharacters().c_str() << "." << endl;
                        Serial << "  In addition, these characters cannot be the first character: " << settings->getWiFiNetworkNameForbiddenStartCharacters().c_str() << "." << endl;
                        
                        Serial << "getWiFiNetworkName - shows name of the Wi-Fi network." << endl;
                    }
                    else if (command.getName() == "setmode")
                    {
                        settings->setMode(command.getArgument().charAt(0) - 48);
                        Serial << "New mode: " << settings->getMode() << "." << endl;
                    }
                    else if (command.getName() == "getmode")
                    {
                        Serial << "Mode: " << settings->getMode() << "." << endl;
                    }
                    else if (command.getName() == "setwifinetworkname")
                    {
                        settings->setWiFiNetworkName(command.getArgument());
                        Serial << "New Wi-Fi network name: " << settings->getWiFiNetworkName() << "." << endl;
                    }
                    else if (command.getName() == "getwifinetworkname")
                    {
                        Serial << "Wi-Fi network name: " << settings->getWiFiNetworkName() << "." <<endl;
                    }
                    else
                    {
                        throw runtime_error("Unknown command. Use help command to get list of all commands.");
                    }
                }
                catch (runtime_error& e)
                {
                    Serial << "[Error] " << e.what() << endl;
                }
            }
        }

    private:

        SerialCommand parceCommand(String str)
        {
            String commandName = "";
            String commandArgument = "";

            str.trim();

            int indexOfFirstSpace = str.indexOf(' ');

            if (indexOfFirstSpace != -1) //  If space was found.
            {
                commandName = str.substring(0, indexOfFirstSpace);
                commandName.trim();

                commandArgument = str.substring(indexOfFirstSpace);
                commandArgument.trim();
            }
            else // If space was not found.
            {
                commandName = str;
            }

            commandName.toLowerCase();
      
            return SerialCommand(commandName, commandArgument);
        }
      
};

#endif
