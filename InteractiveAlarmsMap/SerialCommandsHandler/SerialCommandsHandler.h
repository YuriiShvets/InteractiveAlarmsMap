#ifndef SerialCommandsHandler_h
#define SerialCommandsHandler_h
#pragma once

#include "SerialCommand.h"
#include "../SettingsHandler/SettingsHandler.h"

using namespace std;

//	Handler of serial commands.
//	Serial must be initialized externaly.

class SerialCommandsHandler
{
    private:
        SettingsHandler* settings;

    public:
        SerialCommandsHandler(SettingsHandler* settings)
        {
            this->settings = settings;

            Serial.println("Handler of serial commands was initialized. Use help command to view all commands");
        }

        void Update()
        {
            if (Serial.available())
            {
                String str = Serial.readString();

                Serial.print("->");
                Serial.println(str);
            
                SerialCommand command = parceCommand(str);

                if (command.getName() == "help")
                {
                    Serial.println("  help - shows list of all commands");
                    Serial.println("  setMode <mode> (mode: 0 - standart mode; 1 - interactive alarms mode)");
                    Serial.println("  getMode - shows current work mode");
                }
                else if (command.getName() == "getmode")
                {
                    Serial.print("  Mode: ");
                    Serial.println(settings->getMode());
                }
                else if (command.getName() == "setmode")
                {
                    if (command.getArgument() == "0" || command.getArgument() == "1")
                    {
                        settings->setMode(command.getArgument().charAt(0) - 48);
                        Serial.print("  New mode: ");
                        Serial.println(settings->getMode());
                    }
                    else
                    {
                        Serial.println("  Invalid argument, please use help command for more info.");
                    }
                }
                else
                {
                    Serial.println("  Unknown command");
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

            //  Convertin commandName to lower case.
            transform(commandName.begin(), commandName.end(), commandName.begin(), [](unsigned char c)
            {
                return tolower(c);
            });
      
            return SerialCommand(commandName, commandArgument);
        }
      
};

#endif
