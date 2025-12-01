#include <WiFi.h>

// Nastavitve Access Point
const char* ssid = "ESP32-Chat-Server";
const char* password = "12345678";

WiFiServer server(80);

void setup() {
  Serial.begin(115200);

  // Nastavimo ESP32 kot Access Point
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("Server IP: ");
  Serial.println(IP);

  // Zaženemo strežnik na portu 80
  server.begin();
  Serial.println("Chat server is ready!");
}

void loop() {
  WiFiClient client = server.available();  // preverja, ali je nov klient

  if (client) {
    Serial.println("New client connected!");
    String message = "";

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();       // preberi znak od klienta
        Serial.write(c);              // izpiši znak v Serial Monitor strežnika
        message += c;

        if (c == '\n') {              // konec sporočila
          message = "";               // resetiraj sporočilo
        }
      }
    }

    client.stop();
    Serial.println("Client disconnected.");
  }
}

