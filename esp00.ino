#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Ailah";
const char* password = "12345678";

WebServer server(80);

void setup() {
  Serial.begin(115200); // Debug console
  Serial2.begin(9600, SERIAL_8N1, 16, 17); // UART2 on GPIO16(RX), GPIO17(TX)
  
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Main page
  server.on("/", HTTP_GET, [](){
    server.send(200, "text/html", 
      "<h1>LED CONTROL</h1>"
      "<a href='/on'><button>ON</button></a>"
      "<a href='/off'><button>OFF</button></a>");
    Serial.println("Webpage accessed: /");
  });

  // Turn ON
  server.on("/on", [](){
    Serial2.println("ON"); // Send command to Arduino
    Serial.println("Sent to Arduino: ON");
    server.send(200, "text/plain", "LED ON");
  });

  // Turn OFF
  server.on("/off", [](){
    Serial2.println("OFF"); // Send command to Arduino
    Serial.println("Sent to Arduino: OFF");
    server.send(200, "text/plain", "LED OFF");
  });

  server.begin();
  Serial.println("Web server started.");
}

void loop() {
  server.handleClient();
}
