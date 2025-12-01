#include <WiFi.h>
const char* ssid = "Davids_iPhone2";
const char* password = "*********"; //geslo hotspota

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println("\nConnected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("MAC address: ");
  Serial.println(WiFi.macAddress());
}

void setup() {
  Serial.begin(115200);
  initWiFi();
}

void loop() {
  // put your main code here, to run repeatedly:

}
