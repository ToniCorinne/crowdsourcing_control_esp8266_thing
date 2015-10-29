
/******************************************************************************
HackaDay Super Conference Blink_HelloWorld
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

const int ESP8266_LED = 5;
const int ESP8266_Analog = A0;
const int ESP8266_Digital = 12;


void setup() {
  
  pinMode(ESP8266_LED, OUTPUT);
  pinMode(ESP8266_Analog, INPUT);
  pinMode(ESP8266_Digital, INPUT);
  Serial.begin(9600);
  Serial.println("Hello World!");
  
}

void loop() {

  Serial.print("Analog: ");
  Serial.println(analogRead(ESP8266_Analog));
  
  Serial.print("Digital: ");
  Serial.println(digitalRead(ESP8266_Digital));
  
  digitalWrite(ESP8266_LED, HIGH);
  delay(500);
  digitalWrite(ESP8266_LED, LOW);
  delay(500);
}
