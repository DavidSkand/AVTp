# Vaja 2: ESP-NOW - Pošiljanje analogne vrednosti potenciometra

## Namen vaje
Cilj vaje je preizkusiti **ESP-NOW komunikacijo** med dvema ESP32 napravam, kjer ena bere analogno vrednost potenciometra, druga pa jo prikazuje na serijskem monitorju.

---

## Uporabljene knjižnice
- `WiFi.h` → omogoča uporabo WiFi radia  
- `esp_now.h` → omogoča ESP-NOW komunikacijo  

---

## Sender (ESP32, potenciometer)

- Bere analogno vrednost potenciometra na pinu `34`  
- Pretvori vrednost v dva bajta  
- Pošlje podatke Receiverju preko ESP-NOW  
- Izpiše vrednost na serijski monitor za spremljanje

**Ključna koda:**
```cpp
int potValue = analogRead(POT_PIN);
uint8_t data[2];
data[0] = potValue >> 8;
data[1] = potValue & 0xFF;
esp_now_send(receiverMAC, data, 2);
```
## Receiver (ESP32)
Sprejema podatke od Senderja

Združi prejete bajte nazaj v celotno vrednost

Izpiše vrednost na serijski monitor

Ključna koda:

```cpp
int potValue = (incomingData[0] << 8) | incomingData[1];
Serial.println(potValue);
```
## Ugotovitve
ESP-NOW omogoča hitro peer-to-peer pošiljanje podatkov brez interneta

Callback funkcija omogoča samodejni prejem podatkov

Pretvorba analogne vrednosti v bajte omogoča pošiljanje večjih številk
Vaja je uspešno prikazala, kako ESP32 preko ESP-NOW pošilja in prejema analogne vrednosti.

Spoznal sem uporabo callback funkcij, pretvorbo podatkov v bajte in osnovno peer-to-peer komunikacijo.
