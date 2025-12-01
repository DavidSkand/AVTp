#include <WiFi.h>

// ime našega WiFi (hotspot)
const char* ssid     = "ESP32-Access-Point";
// geslo za WiFi
const char* password = "123456789";

// naredimo server na portu 80 (navaden internet port)
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  
  Serial.print("Setting AP (Access Point)…");
  
  // tukaj naredimo ESP32 kot hotspot
  WiFi.softAP(ssid, password);

  // dobimo IP našega ESP32 (ponavadi 192.168.4.1)
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  
  // zaženemo web server
  server.begin();
}

void loop(){
  // preverimo če se je kdo povezal na naš server
  WiFiClient client = server.available();   

  if (client) {                             
    Serial.println("New Client.");          
    String currentLine = "";                // tukaj shranjujemo kar client piše

    // dokler je client povezan
    while (client.connected()) {            
      
      // če je kaj podatkov od clienta
      if (client.available()) {             
        char c = client.read();             // preberemo en znak
        Serial.write(c);                    // pokažemo znak v serial monitorju

        // če je znak '\n' pomeni nova vrstica
        if (c == '\n') {                    

          // če je vrstica prazna = konec zahtevka
          if (currentLine.length() == 0) {

            // pošljemo odgovor (mora biti tako da deluje v brskalniku)
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // pošljemo HTML stran z "Hello World"
            client.println("<html><body><h1>Hello World</h1></body></html>");
            
            // konec odgovora
            client.println();
            break;  
          } 
          else {
            // začnemo novo vrstico
            currentLine = "";
          }
        } 
        else if (c != '\r') {  
          currentLine += c;    
        }
      }
    }

    // zapremo povezavo
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
 v