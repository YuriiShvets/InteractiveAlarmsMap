#ifndef SerialCommand_h
#define SerialCommand_h
#pragma once

using namespace std;

class SerialCommand
{
    private:
        String name = "";
        String argument = "";

    public:
        SerialCommand(String inName, String inArgument) : name(inName), argument(inArgument)
        {
        }

        String getName() 
        {
            return name;
        }

        String getArgument()
        {
            return argument;
        }
      
};

#endif
