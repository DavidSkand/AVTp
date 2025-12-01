# Vaja 1: ESP32 Access Point in Web Server

## Cilj vaje
- Naučiti se ustvariti ESP32 kot WiFi Access Point (AP)
- Naučiti se vzpostaviti web server na ESP32
- Naučiti se komunicirati med ESP32 in klientom (telefon, laptop ali drugi ESP32)

## Kaj sem se novega naučil
- ESP32 lahko deluje kot **WiFi Hotspot** preko `WiFi.softAP(ssid, password)`
- Web server na ESP32 lahko posluša na **portu 80** (`WiFiServer server(80)`)
- Kako brati HTTP zahteve po **vrsticah** in pošiljati odgovor
- Pomen posebnih znakov `\r` in `\n` v HTTP protokolu
- Povezava med kodo, IP naslovom AP in brskalnikom/klientom

## Del kode in razlaga
```cpp
// Nastavimo ESP32 kot Access Point
WiFi.softAP(ssid, password);

// Zaženemo web server na portu 80
WiFiServer server(80);
server.begin();

// Branje podatkov od klienta
String currentLine = "";
while (client.connected()) {
    if (client.available()) {
        char c = client.read();
        currentLine += c;

        // Če dobimo prazno vrstico (dve znaka \r\n), pošljemo odgovor
        if (c == '\n' && currentLine.length() == 2) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.println("<html><body><h1>Hello World</h1></body></html>");
        }
    }
}
currentLine.length() == 2 → preveri prazno vrstico, ki pomeni konec HTTP zahtevka

\r = carriage return (vrni se na začetek vrstice)

\n = newline (nova vrstica)

Kaj vpliva na delovanje
IP naslov AP: naprave ga morajo poznati za povezavo

Port serverja: mora biti isti kot klient pričakuje

Zaporedje znakov \r\n: pravilno zazna konec zahtevka

Slike / Diagram
Slika vezja ESP32

Posnetek serijskega monitorja: “New Client” in IP naslov

Zaključek
Razumel sem, kako ESP32 deluje kot AP

Spoznal sem HTTP komunikacijo in kako se ESP32 odzove na klienta

Naučil sem se pomena posebnih znakov v protokolu in kako kontrolirati konec zahtevka