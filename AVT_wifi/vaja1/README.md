# Vaja 1: Povezava ESP32 na WiFi Access Point (HotSpot)

## Cilj vaje
- Naučiti se, kako se ESP32 poveže na WiFi dostopno točko (HotSpot).  
- Preveriti IP naslov, ki ga ESP32 dobi od HotSpot-a.  
- Preveriti MAC naslov ESP32 naprave.  

## Kaj sem se novega naučil
- ESP32 lahko deluje kot **WiFi klient (Station)** z `WiFi.mode(WIFI_STA)`  
- Kako uporabiti `WiFi.begin(ssid, password)` za povezavo na dostopno točko  
- Kako pridobiti IP naslov z `WiFi.localIP()`  
- Kako pridobiti MAC naslov z `WiFi.macAddress()`  
- Kako spremljati stanje povezave z `WiFi.status()`  

## Del kode in razlaga
```cpp
#include <WiFi.h>

// WiFi HotSpot credentials
const char* ssid = "David's iPhone (2)";
const char* password = "gorila1234";

void initWiFi() {
  WiFi.mode(WIFI_STA);          // ESP32 deluje kot WiFi klient
  WiFi.begin(ssid, password);   // Povežemo se na HotSpot

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }

  // Ko je povezava vzpostavljena, izpišemo IP in MAC
  Serial.println("\nConnected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("MAC address: ");
  Serial.println(WiFi.macAddress());
}

void setup() {
  Serial.begin(115200);
  initWiFi();  // Povežemo se na HotSpot
}

void loop() {
  // Nič ni potrebno za ta del vaje
}
Kaj počne posamezen del kode
WiFi.mode(WIFI_STA) → ESP32 postane klient (se povezuje na WiFi)

WiFi.begin(ssid, password) → začne povezavo na tvoj telefon HotSpot

while (WiFi.status() != WL_CONNECTED) → počaka, da je povezava uspešna

WiFi.localIP() → vrne IP naslov ESP32, ki ga dodeli HotSpot

WiFi.macAddress() → vrne MAC naslov ESP32

Rezultat v Serial Monitorju
Primer izpisa:

ruby
Kopiraj kodo
Connecting to WiFi...
Connected!
IP address: 192.168.43.123
MAC address: 24:6F:28:AA:BB:CC
IP address → naslov, ki ga ESP32 dobi od HotSpot-a

MAC address → edinstvena identifikacija ESP32 naprave

Zaključek
ESP32 se uspešno poveže na HotSpot.

Spoznal sem, kako pridobiti IP in MAC naslov ESP32.

Naučil sem se, kako preverjati stanje WiFi povezave in kako uporabljati vgrajene funkcije WiFi.localIP() in WiFi.macAddress().