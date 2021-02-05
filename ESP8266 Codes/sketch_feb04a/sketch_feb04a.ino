#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <SoftwareSerial.h>

//SoftwareSerial mySerial(2, 3);

const char *ssid = "ESPap";
const char *password = "thereisnospoon";

String stringBuffer="";
String data;

IPAddress myIP = WiFi.softAPIP();
ESP8266WebServer server(myIP, 80);

void setup() {
  Serial.begin(115200);
  //mySerial.begin(115200);
  WiFi.softAP(ssid, password);

  server.begin();
  server.on("/", sendAcceleration); //send
}

void sendAcceleration() {
  server.send(200, "text/plain", data);
}

void loop() {
  server.handleClient();
  
  boolean stringReady = false;

  while(Serial.available()){
    stringBuffer = Serial.readStringUntil('\n');
    stringReady = true;  
  }
  
  if(stringReady){
    data = stringBuffer;
    //sendAcceleration();
    //Serial.println(data);
  }
}
