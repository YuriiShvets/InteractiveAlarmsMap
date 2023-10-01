#ifndef SerialCommandsHandler_h
#define SerialCommandsHandler_h
#pragma once

#include "SerialCommand.h"
#include "../SettingsHandler/SettingsHandler.h"

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

            Serial.println("Handler of serial commands was initialized. Use help command to view all commands.");
        }

        void Update()
        {
            if (Serial.available())
            {
                String str = Serial.readString();

                Serial.print(" -> ");
                Serial.println(str);
            
                //  TODO suround with try-catch.

                try
                {
                    SerialCommand command = parceCommand(str);

                    if (command.getName() == "help")
                    {
                        Serial.println("help - shows list of all commands.");
                        Serial.println("setMode <mode> (mode: 0 - standart mode; 1 - interactive alarms mode) - command for mode setting.");
                        Serial.println("getMode - shows current work mode.");
                        Serial.println("setWiFiNetworkName <WiFiNetworkName> - command for setting of Wi-Fi network name.");
                        Serial.println("  Wi-Fi network can be any alphanumeric, case-sensitive entry from 2 to 32 characters. The printable characters plus the space are allowed, but these six characters are not:");
                        Serial.println("  ? , \", $, [, \\, ], and +.");
                        Serial.println("  In addition, these three characters cannot be the first character:");
                        Serial.println("  !, #, and ;.");
                        Serial.println("getWiFiNetworkName - shows name of the Wi-Fi network.");
                    }
                    else if (command.getName() == "setmode")
                    {
                        settings->setMode(command.getArgument().charAt(0) - 48);
                        Serial.print("New mode: ");
                        Serial.print(settings->getMode());
                        Serial.println(".");
                    }
                    else if (command.getName() == "getmode")
                    {
                        Serial.print("Mode: ");
                        Serial.print(settings->getMode());
                        Serial.println(".");
                    }
                    else if (command.getName() == "setwifinetworkname")
                    {
                        settings->setWiFiNetworkName(command.getArgument());
                        Serial.print("New Wi-Fi network name: ");
                        Serial.print(settings->getWiFiNetworkName());
                        Serial.println(".");
                    }
                    else if (command.getName() == "getwifinetworkname")
                    {
                        Serial.print("Wi-Fi network name: ");
                        Serial.print(settings->getWiFiNetworkName());
                        Serial.println(".");
                    }
                    else
                    {
                        throw runtime_error("Unknown command. Use help command to get list of all commands.");
                    }
                }
                catch (runtime_error& e)
                {
                    Serial.print("[Error] ");
                    Serial.println(e.what());
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
