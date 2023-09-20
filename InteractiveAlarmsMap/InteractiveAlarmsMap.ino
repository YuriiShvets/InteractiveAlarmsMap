#include "SerialCommandsHandler/SerialCommandsHandler.h"
#include "SettingsHandler/SettingsHandler.h"

void setup() 
{
  delay(5000);  //  TODO delete this.
  
  delay(1000);

  // Initialization;
  Serial.begin(115200);
  Serial.println();

  SettingsHandler settings = SettingsHandler();
  
  SerialCommandsHandler serialCommandsHandler = SerialCommandsHandler(&settings);
  
  delay(1000);

  // Main loop
  while (true) 
  {
    serialCommandsHandler.Update();
    if(settings.getMode() == 0) //  If in standart mode.
    {
      //  TODO complete.
    }
    else if (settings.getMode() == 1) //  If in interactive alarms mode.
    {
      // TODO complete.
    }
  }
}

void loop() 
{
}
