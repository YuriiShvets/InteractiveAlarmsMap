#ifndef SerialCommandsHandler_h
#define SerialCommandsHandler_h
#pragma once

#include "SerialCommand.h"

using namespace std;

//	Handler of serial commands.
//	Serial must be initialized externaly.

class SerialCommandsHandler
{

  public:
    SerialCommandsHandler()
    {
        Serial.println("Handler of serial conmmands initialized. Use help to view all commands");
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
                Serial.println("  help - show list of all commands");
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
