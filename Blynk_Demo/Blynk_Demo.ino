/******************************************************************************
HackaDay Super Conference Blynk_Demo
Toni Klopfenstein @ SparkFun Electronics
OCtober 2015
<github repository address>

Sketch to demo the ESP8266 Thing in the Blynk app.

Resources:
ESP8266 Arduino Add-On Required
Blynk app

Development environment specifics:
Arduino 1.6.5+ with the ESP8266 Thing()

This code is released under the [MIT License](http://opensource.org/licenses/MIT).
Please review the LICENSE.md file included with this example. If you have any questions 
or concerns with licensing, please contact techsupport@sparkfun.com.

Distributed as-is; no warranty is given.
******************************************************************************
 1. Connect LED to Pin 4
 2. Connect button to pin 12
 
 In the Blynk App:
  2. Create New Project
  3. Email yourself Auth Token. You can do it later at any time
  4. Add a Button Widget. Select pin gp4 in Widget's settings
  5. Add a LED widget. Select pin V1 in Widget's settings
  6. Add a gauge widget. Select pin adc0 in Widget's settings
******************************************************************************/

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App. Go to the Project Settings (nut icon).
char auth[] = "64a41877dee64ba497d4ba701cd4fd5a";

void setup() 
{
  
  Blynk.begin(auth, "sparkfun-guest", "sparkfun6333");
  
}



void loop() 
{
  Blynk.run();
}
