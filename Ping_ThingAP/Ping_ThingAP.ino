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
const char WiFiSSID[] = "ESP8266 Thing - YOUR NAME macID";
const char WiFiPSK[] = "superconference15";
const char ledOn[] = "192.168.4.1/led/0";
const char ledOff[] = "192.168.4.1/led/1";
const int httpPort = 80;

/////////////////////
// Pin Definitions //
/////////////////////
const int ESP8266_OnBoardLED = 5;
const int ESP8266_ButtonOne = 4;
const int ESP8266_ButtonTwo = 12;

/////////////////////
//  WiFi Function  //
/////////////////////
void connectWiFi()
{
  byte ledStatus = LOW;

  // Set WiFi mode to station (as opposed to AP or AP_STA)
  WiFi.mode(WIFI_STA);

  // WiFI.begin([ssid], [passkey]) initiates a WiFI connection
  // to the stated [ssid], using the [passkey] as a WPA, WPA2,
  // or WEP passphrase.
  WiFi.begin(WiFiSSID, WiFiPSK);

  // Use the WiFi.status() function to check if the ESP8266
  // is connected to a WiFi network.
  while (WiFi.status() != WL_CONNECTED)
  {
    // Blink the on-board LED
    digitalWrite(ESP8266_OnBoardLED, ledStatus); // Write LED high/low
    ledStatus = (ledStatus == HIGH) ? LOW : HIGH;

    // Delays allow the ESP8266 to perform critical tasks
    // defined outside of the sketch. These tasks include
    // setting up, and maintaining, a WiFi connection.
    delay(100);
    // Potentially infinite loops are generally dangerous.
    // Add delays -- allowing the processor to perform other
    // tasks -- wherever possible.
  }
}

void initHardware()
{
  Serial.begin(115200);
  pinMode(ESP8266_ButtonOne, INPUT);
  pinMode(ESP8266_ButtonTwo, INPUT);
  pinMode(ESP8266_OnBoardLED, OUTPUT);
  digitalWrite(ESP8266_OnBoardLED, LOW);
}

void setup(){
  initHardware();
  connectWiFi();
}
///////////////////////
// Ping the Thing    //
///////////////////////
void loop(){
  
  // Onboard LED turns on when we enter, it'll go off when we 
  // successfully GET data.
  digitalWrite(ESP8266_OnBoardLED, HIGH);
  WiFiClient client;
  
  if (digitalRead(ESP8266_ButtonOne) == HIGH){
    if (!client.connect(ledOn, httpPort))
    {
      return;    
    }
  }

  else if (digitalRead(ESP8266_ButtonTwo) == HIGH){
    if (!client.connect(ledOff, httpPort))
    {
      return;    
    }
  }

  digitalWrite(ESP8266_OnBoardLED, LOW);
}

