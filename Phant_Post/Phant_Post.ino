/******************************************************************************
HackaDay Super Conference Phant_Post
Toni Klopfenstein @ SparkFun Electronics
OCtober 2015
<github repository address>

Intro sketch to test basic features of the ESP8266 Thing.

Resources:
ESP8266 Arduino Add-On Required

Development environment specifics:
Arduino 1.6.5+ with the ESP8266 Thing()

This code is released under the [MIT License](http://opensource.org/licenses/MIT).
Please review the LICENSE.md file included with this example. If you have any questions 
or concerns with licensing, please contact techsupport@sparkfun.com.

Distributed as-is; no warranty is given.
******************************************************************************/

#include <ESP8266WiFi.h>
#include <Phant.h>

//////////////////////
// WiFi Definitions //
//////////////////////
const char WiFiSSID[] = "sparkfun-guest";
const char WiFiPSK[] = "sparkfun6333";

/////////////////////
// Pin Definitions //
/////////////////////
const int ESP8266_OnBoardLED = 5;
const int ESP8266_Analog = A0;
const int ESP8266_Button = 12;
const int ESP8266_LED = 4;

////////////////
// Phant Keys //
////////////////
const char PhantHost[] = "data.sparkfun.com";
const char PublicKey[] = "wpvZ9pE1qbFJAjaGd3bn";
const char PrivateKey[] = "wzeB1z0xWNt1YJX27xdg";

/////////////////
// Post Timing //
/////////////////
const unsigned long postRate = 30000;
unsigned long lastPost = 0;

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

//////////////////////////
// Phant Post Function  //
//////////////////////////
int postToPhant()
{
  // Onboard LED turns on when we enter, it'll go off when we 
  // successfully post.
  digitalWrite(ESP8266_LED, HIGH);

  // Declare an object from the Phant library - phant
  Phant phant(PhantHost, PublicKey, PrivateKey);

  // Do a little work to get a unique-ish name. Append the
  // last two bytes of the MAC (HEX'd) to "Thing-":
  uint8_t mac[WL_MAC_ADDR_LENGTH];
  WiFi.macAddress(mac);
  String macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) +
                 String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
  macID.toUpperCase();
  String postedID = "Thing-" + macID;

  // Add the four field/value pairs defined by our stream:
  phant.add("id", postedID);
  phant.add("analog", analogRead(ESP8266_Analog));
  phant.add("digital", digitalRead(ESP8266_Button));
  phant.add("time", millis());

  // Now connect to data.sparkfun.com, and post our data:
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(PhantHost, httpPort)) 
  {
    // If we fail to connect, return 0.
    return 0;
  }
  // If we successfully connected, print our Phant post:
  client.print(phant.post());

  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
  }

  // Before we exit, turn the LED off.
  digitalWrite(ESP8266_LED, LOW);

  return 1; // Return success
}

/////////////////
// Setup Loop  //
/////////////////
void setup() {
  pinMode(ESP8266_Button, INPUT);
  pinMode(ESP8266_LED, OUTPUT);
  pinMode(ESP8266_OnBoardLED, OUTPUT);
  digitalWrite(ESP8266_LED, LOW);
  digitalWrite(ESP8266_OnBoardLED, LOW);
  connectWiFi();
}

/////////////////
//  Main Loop  //
/////////////////
void loop() {
 if (lastPost + postRate <= millis())
  {
    if (postToPhant())
      lastPost = millis();
    else
      delay(100);    
  }
}

