#define UART_BAUD 115200

const char *ssid = "ESP";
const char *pw = "password";
const int port = 5555;

#include <ESP8266WiFi.h>
#include <WiFiClient.h>

WiFiServer server(port);
WiFiClient client;

uint8_t buf1[1024];
uint8_t i1 = 0;

uint8_t buf2[1024];
uint8_t i2 = 0;

void setup() {
  // put your setup code here, to run once:
  delay(500);
  Serial.begin(UART_BAUD);
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, pw);
  //WiFi.begin(ssid, pw);

//  while(WiFi.status() != WL_CONNECTED){
//     Serial.print(".");
//     delay(100);  
//  }

  //config static IP
//  IPAddress ip(192, 168, 18, 50);
//  IPAddress gateway(192, 168, 18, 1);
//  IPAddress subnet (255, 255, 255, 0);
//  WiFi.config(ip, gateway, subnet);

//  Serial.println("");
//  Serial.print("Connected to ");
//  Serial.println(ssid);
//  Serial.print("IP address: ");
//  Serial.println(WiFi.localIP());
  server.begin();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(!client.connected()){
    client = server.available();
    return;  
  }

   //read data from client
  if(client.available()){
    while(client.available()){
      buf1[i1] = (uint8_t) client.read();
      if(i1 < 1023) i1++;  
    }

    Serial.write(buf1, i1);
    i1 = 0;
  }

  //send data to client
  if(Serial.available()){
    while(Serial.available()){
      buf2[i2] = (char) Serial.read();
      if(i2 < 1023) i2++;  
    }

    client.write((char*) buf2, i2);
    i2 = 0;
  }
}
