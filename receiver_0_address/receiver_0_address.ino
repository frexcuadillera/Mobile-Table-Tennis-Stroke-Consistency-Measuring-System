/*
* Arduino Wireless Communication Tutorial
*       Example 1 - Receiver Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  radio.begin();
  radio.openReadingPipe(0, 0xE8E8F0F0E1LL);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  digitalWrite(LED_BUILTIN, HIGH);
}
void loop() {
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    Serial.println(text);
  }

  digitalWrite(LED_BUILTIN, HIGH);
}
