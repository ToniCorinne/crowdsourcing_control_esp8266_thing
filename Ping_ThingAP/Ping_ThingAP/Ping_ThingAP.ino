/******************************************************************************
HackaDay Super Conference Phant_Get
Toni Klopfenstein @ SparkFun Electronics
OCtober 2015
<github repository address>

Sketch to pull data from a second ESP8266 on the ESP8266 Thing.

Resources:
ESP8266 Arduino Add-On Required

Development environment specifics:
Arduino 1.6.5+ with the ESP8266 Thing()

Based on ESP8266_Phant example by Jim Lindblom, SparkFun Electronics 2015

This code is released under the [MIT License](http://opensource.org/licenses/MIT).
Please review the LICENSE.md file included with this example. If you have any questions 
or concerns with licensing, please contact techsupport@sparkfun.com.

Distributed as-is; no warranty is given.
******************************************************************************/

#include <ESP8266WiFi.h>

//////////////////////
// WiFi Definitions //
//////////////////////
const char WiFiAPPSK[] = "sanfran15";

WiFiServer server(80);

/////////////////////
// Pin Definitions //
/////////////////////
const int ESP8266_OnBoardLED = 5; 
const int ESP8266_LED_Green = 0;
const int ESP8266_LED_Red = 4;
const int ESP8266_LED_Blue = 13;

/////////////////////
//  WiFi Function  //
/////////////////////
void setupWiFi()
{
  WiFi.mode(WIFI_AP);

  // Do a little work to get a unique-ish name. Append the
  // last two bytes of the MAC (HEX'd) to "ThingDev-":
  uint8_t mac[WL_MAC_ADDR_LENGTH];
  WiFi.softAPmacAddress(mac);
  String macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) +
                 String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
  macID.toUpperCase();
  String AP_NameString = "Toni" + macID;

  char AP_NameChar[AP_NameString.length() + 1];
  memset(AP_NameChar, 0, AP_NameString.length() + 1);

  for (int i=0; i<AP_NameString.length(); i++)
    AP_NameChar[i] = AP_NameString.charAt(i);

  WiFi.softAP(AP_NameChar, WiFiAPPSK);
}


void initHardware()
{
  Serial.begin(115200);
  pinMode(ESP8266_OnBoardLED, OUTPUT);
  pinMode(ESP8266_LED_Green, OUTPUT);
  pinMode(ESP8266_LED_Blue, OUTPUT);
  pinMode(ESP8266_LED_Red, OUTPUT);
  digitalWrite(ESP8266_OnBoardLED, LOW);
  digitalWrite(ESP8266_LED_Green, LOW);
  digitalWrite(ESP8266_LED_Blue, LOW);
  digitalWrite(ESP8266_LED_Red, LOW);
  
}

void setup(){
  initHardware();
  server.begin();
  setupWiFi();
}

///////////////////////
// Ping the Thing    //
///////////////////////
void loop() 
{
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  // Match the request
  int valGreen = -1; //Input for Green LED
  int valRed = -1; //Input for Red LED
  int valBlue = -1; //Input for Blue LED
  
  if (req.indexOf("/green/0") != -1)
    valGreen = 1; // Will write Green LED high
  else if (req.indexOf("/green/1") != -1)
    valGreen = 0; // Will write Green LED low
  else if (req.indexOf("/red/0") != -1)
    valRed = 1; // Will write Red LED high
  else if (req.indexOf("/red/1") != -1)
    valRed = 0; // Will write Red LED low
  else if (req.indexOf("/blue/0") != -1)
    valRed = 1; // Will write Blue LED high 
  else if (req.indexOf("/blue/1") != -1)
    valRed = 0; // Will write Blue LED low 
  // Otherwise request will be invalid. We'll say as much in HTML

  // Set LEDs according to the request
  if (valGreen >= 0){
    digitalWrite(ESP8266_LED_Green, valGreen);
  }
  else if (valRed >= 0){
    digitalWrite(ESP8266_LED_Red, valRed);
  }
  else if (valBlue >= 0){
    digitalWrite(ESP8266_LED_Blue, valBlue);
  }
  
  client.flush();

  // Prepare the response. Start with the common header:
  String s = "HTTP/1.1 200 OK\r\n";
  s += "Content-Type: text/html\r\n\r\n";
  s += "<!DOCTYPE HTML>\r\n<html>\r\n";
  // If we're setting the LEDs, print out a message saying we did
  if (valGreen >= 0 || valRed >= 0 || valBlue >= 0)
  {
    s += "Green = ";
    s += (valGreen)?"off":"on";
    s += "; ";
    s += "Red = ";
    s += (valRed)?"off":"on";
    s += "; ";
    s += "Blue = ";
    s += (valBlue)?"off":"on";
  }
  else
  {
    s += "Invalid Request.<br> Try /green/1, /green/0, /red/1, /red/0, /blue/1, or /blue/0.";
  }
  s += "</html>\n";

  // Send the response to the client
  client.print(s);
  delay(1);

}

