#include <nRF24L01.h>
#include <RF24.h>
#include <SPI.h>


RF24 radio(9, 10);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, 0xE8E8F0F0E1LL);
  radio.setChannel(0x77);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_1MBPS);
  radio.setPayloadSize(32);
  radio.enableDynamicPayloads();
  radio.startListening();  

}

void loop() {
  if(radio.available()){
    char text[32] = "";
    radio.read(&text, sizeof(text));
    Serial.println(text);
  }
}
