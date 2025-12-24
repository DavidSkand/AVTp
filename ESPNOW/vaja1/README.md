# Vaja 1: ESP-NOW - Sender in Receiver

## Namen vaje
Cilj vaje je spoznati in implementirati **ESP-NOW protokol** na ESP32 razvojni plošči.  
Vaja vključuje dve napravi:

- **Receiver (sprejemnik)** → prejema sporočila
- **Sender (pošiljatelj)** → pošilja sporočila receiverju

---

## Uporabljene knjižnice
- `WiFi.h` → uporaba WiFi radia, ki je nujen za ESP-NOW  
- `esp_now.h` → implementacija ESP-NOW protokola  

---

## Receiver (sprejemnik)

```cpp
WiFi.mode(WIFI_STA);                  // Nastavi ESP32 v WiFi Station mode
esp_now_init();                       // Inicializira ESP-NOW protokol
esp_now_register_recv_cb(onDataReceived); // Registrira funkcijo, ki se pokliče ob prejemu sporočila

void onDataReceived(const uint8_t *mac, const uint8_t *incomingData, int len) {
    char macStr[18];
    // Pretvori 6 bajtov MAC naslova v berljiv niz "XX:XX:XX:XX:XX:XX"
    snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X",
             mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    Serial.print("Received message from: "); 
    Serial.println(macStr);
    Serial.print("Message length: "); 
    Serial.println(len);
}
Pojasnilo:

WiFi.mode(WIFI_STA) → STA mode omogoča ESP32, da deluje kot naprava v omrežju

esp_now_init() → preveri, ali je ESP-NOW uspešno inicializiran

esp_now_register_recv_cb() → callback funkcija, ki se sproži, ko ESP32 prejme sporočilo

onDataReceived() → izpiše MAC naslov pošiljatelja in dolžino prejetega sporočila

```

## Sender (pošiljatelj)
```cpp
WiFi.mode(WIFI_STA);                  // STA mode za pošiljanje
esp_now_init();                       // Inicializacija ESP-NOW

// Nastavitev peer naprave (receiver)
esp_now_peer_info_t peerInfo;
memcpy(peerInfo.peer_addr, receiverMAC, 6); // Kopira MAC naslov receiverja
peerInfo.channel = 0;  
peerInfo.encrypt = false;
esp_now_add_peer(&peerInfo);          // Registrira peer napravo

// Pošiljanje sporočila
esp_now_send(receiverMAC, (uint8_t *)message, strlen(message));
delay(2000);                          // Pošlji sporočilo vsaki 2 sekundi
Pojasnilo:

memcpy(peerInfo.peer_addr, receiverMAC, 6) → MAC naslov receiverja je potreben za pošiljanje sporočila

peerInfo.channel → določa kanal WiFi radia

peerInfo.encrypt → false pomeni brez šifriranja

esp_now_send() → pošlje sporočilo kot bajte

delay(2000) → pošiljanje vsaki 2 sekundi
```

## Ugotovitve
ESP-NOW omogoča peer-to-peer komunikacijo brez interneta.

Callback funkcije omogočajo samodejni prejem sporočil.

MAC naslov je edinstven identifikator peer naprave.

ESP32 lahko komunicira brez WiFi Access Pointa, le v STA mode.

## Zaključek
Vaja uspešno prikazuje delovanje ESP-NOW protokola na ESP32.

Spoznal sem osnovne koncepte peer-to-peer komunikacije, uporabo WiFi radia brez interneta in pravilno obdelavo pošiljanja in prejemanja podatkov.
