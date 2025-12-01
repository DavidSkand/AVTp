#include <WiFi.h>

// WiFi Access Point strežnika
const char* ssid = "ESP32-Chat-Server";  // ime AP strežnika
const char* password = "12345678";       // geslo AP strežnika

const char* serverIP = "192.168.4.1";   // IP strežnika (preveri v Serial Monitorju strežnika)
WiFiClient client;

void setup() {
  Serial.begin(115200);

  // Povežemo ESP32 klient na strežnikov AP
  WiFi.begin(ssid, password);
  Serial.print("Connecting to server...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\nConnected to server!");

  // Vzpostavimo TCP povezavo na port 80
  if (client.connect(serverIP, 80)) {
    Serial.println("Connected to chat server!");
  }
}

void loop() {
  // Preberemo sporočilo iz Serial Monitorja in ga pošljemo strežniku
  if (Serial.available()) {
    String msg = Serial.readStringUntil('\n');  // preberi eno vrstico
    client.println(msg);                         // pošlji sporočilo strežniku
  }
}
