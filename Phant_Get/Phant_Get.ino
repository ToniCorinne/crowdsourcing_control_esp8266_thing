/******************************************************************************
HackaDay Super Conference Phant_Get
Toni Klopfenstein @ SparkFun Electronics
OCtober 2015
<github repository address>

Sketch to pull data from Phant on the ESP8266 Thing.

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
const int ESP8266_LED = 4;


////////////////
// Phant Keys //
////////////////
const char PhantHost[] = "data.sparkfun.com";
const char PublicKey[] = "wpvZ9pE1qbFJAjaGd3bn";
const char PrivateKey[] = "wzeB1z0xWNt1YJX27xdg";


/////////////////
// Get Timing  //
/////////////////
const unsigned long getRate = 30000;
unsigned long lastGet = 0;


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

///////////////////////
// GET from Phant   //
///////////////////////
void getPhant(){
  
  // Onboard LED turns on when we enter, it'll go off when we 
  // successfully post.
  digitalWrite(ESP8266_LED, HIGH);

  // Declare an object from the Phant library - phant
  Phant phant(PhantHost, PublicKey, PrivateKey);

// Construct HTTP GET request
  String feedback = "GET /output" + PublicKey + ".csv?page=1";
  feedback += " HTTP/1.1\n Host: ";
  feedback += http_site;
  feedback += "\n Connection: close\n\n";

  Serial.print(result); 
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
  Serial.begin(115200);
  
}

/////////////////
//  Main Loop  //
/////////////////
void loop() {
  
  getPhant();
  delay(500);

}

