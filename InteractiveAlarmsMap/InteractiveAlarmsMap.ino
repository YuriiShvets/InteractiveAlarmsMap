#include "SerialCommandsHandler/SerialCommandsHandler.h"

void setup() 
{
  delay(5000);  //  TODO delete this.
  
  delay(1000);

  // Initialization;
  Serial.begin(115200);
  SerialCommandsHandler serialCommandsHandler = SerialCommandsHandler(); 
  
  delay(1000);

  // Main loop
  while (true) 
  {
    serialCommandsHandler.Update();
  }
}

void loop() 
{
}
