//  -fexceptions flag should be added to compiler.cpp.extra_flags in platform.txt (for enabling of exeptions handling).
//  C++ Exceptions option in Tools panel of Arduino IDE must be enabled.

//  TODO write logger?

#include "SerialCommandsHandler/SerialCommandsHandler.h"
#include "SettingsHandler/SettingsHandler.h"
#include "AddressLEDsController/AddressLEDsController.h"
#include "Animations/SimpleYellowAndBlueAnimation.h"
#include "Libraries/Streaming/Streaming.h"

void setup() 
{
  delay(5000);  //  TODO delete this.

  // Initialization.
  delay(1000);

  Serial.begin(115200);
  Serial << endl;

  SettingsHandler settings = SettingsHandler();
  
  SerialCommandsHandler serialCommandsHandler = SerialCommandsHandler(&settings);

  AddressLEDsController addressLEDsController = AddressLEDsController(3, D8); //  (number of LEDs, control PIN).

  SimpleYellowAndBlueAnimation simpleYellowAndBlueAnimation = SimpleYellowAndBlueAnimation(7, &addressLEDsController); // (Color change period, controller of address LEDs).
  
  delay(1000);

  // Main loop.
  while (true) 
  {
    serialCommandsHandler.Update();
    
    if(settings.getMode() == 0) //  If in standart mode.
    {
      simpleYellowAndBlueAnimation.Update();
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
