#include <ESP8266WiFi.h>

const char* ssid = "Shehyee";
const char* password = "shehyee123";

WiFiServer server(80);

String header;

void setup() {
Serial.begin(115200);

WiFi.begin(ssid, password);
IPAddress ip(192,168,0,51);
IPAddress gateway(192,168,0,1);
IPAddress subnet(255,255,255,0);
WiFi.config(ip,gateway,subnet);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected.");
Serial.println("IP address: ");
Serial.println(WiFi.localIP());
server.begin();
}

void loop(){
WiFiClient client = server.available();

if (client) {
Serial.println("New Client.");
String currentLine = "";
while (client.connected()) {
if (client.available()) {
char c = client.read();
Serial.write(c);

95

header += c;
if (c == '\n') {
if (currentLine.length() == 0) {
client.println("HTTP/1.1 200 OK");
client.println("Content-type:text/html");
client.println("Connection: close");
client.println();

if (header.indexOf("GET /5/on") >= 0) {
Serial.println("GPIO 5 on");
output5State = "on";
digitalWrite(output5, HIGH);
} else if (header.indexOf("GET /5/off") >= 0) {
Serial.println("GPIO 5 off");
output5State = "off";
digitalWrite(output5, LOW);
}

client.println("<!DOCTYPE html><html>");

client.println("<body style='background:transparent' onload='window.close();'>");

client.println("</body></html>");

// The HTTP response ends with another blank line
client.println();
// Break out of the while loop
break;

96

} else { // if you got a newline, then clear currentLine
currentLine = "";
}
} else if (c != '\r') { // if you got anything else but a carriage return character,
currentLine += c; // add it to the end of the currentLine
}
}
}
// Clear the header variable
header = "";
// Close the connection
client.stop();
Serial.println("Client disconnected.");
Serial.println("");
}
}
