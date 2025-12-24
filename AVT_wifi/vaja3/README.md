# Vaja 3: Enostaven Chat Room z ESP32

## Cilj vaje
- Ena ESP32 deluje kot **strežnik (Access Point)**.  
- Več ESP32 deluje kot **klienti**, ki pošiljajo sporočila.  
- Sporočila se prikazujejo na Serial Monitor strežnika.  

---

## Strežnik (ESP32 kot AP)
```cpp
#include <WiFi.h>

const char* ssid = "ESP32-Chat-Server";
const char* password = "12345678";
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, password);           // ustvari Access Point
  Serial.print("Server IP: "); 
  Serial.println(WiFi.softAPIP());       // prikaže IP strežnika
  server.begin();                         // zaženi strežnik
}

void loop() {
  WiFiClient client = server.available(); // preveri nove klient povezave
  if (client) {
    Serial.println("New client connected!");
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);                  // izpiše sporočilo klienta
      }
    }
    client.stop();
    Serial.println("Client disconnected.");
  }
}
```
## Klient (ESP32 povezan na strežnik)
```cpp
#include <WiFi.h>

const char* ssid = "ESP32-Chat-Server";
const char* password = "12345678";
const char* serverIP = "192.168.4.1";
WiFiClient client;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);             // poveži se na strežnik
  while (WiFi.status() != WL_CONNECTED) delay(1000);
  client.connect(serverIP, 80);           // vzpostavi TCP povezavo
}

void loop() {
  if (Serial.available()) {
    String msg = Serial.readStringUntil('\n');
    client.println(msg);                   // pošlji sporočilo strežniku
  }
}
```
## Najpomembnejše stvari
WiFi.softAP(ssid, password) → ustvari strežnikov WiFi

WiFiServer server(80) → posluša na portu 80

server.available() → preveri nove klient povezave

Serial.write(c) → izpiše sporočilo klienta

Klient: WiFi.begin(ssid, password) poveže ESP32 na strežnik

client.connect(serverIP, 80) → vzpostavi TCP povezavo

Serial.readStringUntil('\n') → prebere sporočilo, ki ga pošlješ v Serial Monitor

client.println(msg) → pošlje sporočilo strežniku

## Zaključek
Uspelo mi je narediti enostaven chat room z ESP32 napravami.

Spoznal sem osnovno Access Point + Client komunikacijo preko WiFi.


Serial Monitor se uporablja kot tipkovnica in prikaz sporočil.
