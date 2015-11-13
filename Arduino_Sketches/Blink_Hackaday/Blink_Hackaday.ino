
/******************************************************************************
HackaDay Super Conference Blink_Hackaday
Toni Klopfenstein @ SparkFun Electronics
OCtober 2015
www.github.com/sparkfun/crowdsourcing_control_esp8266_thing

Intro sketch to test basic features of the ESP8266 Thing.

Resources:
ESP8266 Arduino Add-On Required

Development environment specifics:
Arduino 1.6.5+ with the ESP8266 Thing()

Based on ESP8266 Blink example by Jim Lindblom, SparkFun Electronics 2015

This code is released under the [MIT License](http://opensource.org/licenses/MIT).
Please review the LICENSE.md file included with this example. If you have any questions 
or concerns with licensing, please contact techsupport@sparkfun.com.

Distributed as-is; no warranty is given.
******************************************************************************/

const int ESP8266_OnBoardLED = 5;
const int ESP8266_Analog = A0;
const int ESP8266_Button = 12;
const int ESP8266_LED = 4;


void setup() {
  
  pinMode(ESP8266_OnBoardLED, OUTPUT);
  //pinMode(ESP8266_Analog, INPUT);
  pinMode(ESP8266_Button, INPUT);
  pinMode(ESP8266_LED, OUTPUT);
}

void loop() {

  int input = analogRead(ESP8266_Analog);
  analogWrite(ESP8266_LED, input);
  
  digitalWrite(ESP8266_OnBoardLED, LOW);
  
  while (digitalRead(ESP8266_Button)==LOW)
  {
    digitalWrite(ESP8266_OnBoardLED, HIGH);
  }

}

