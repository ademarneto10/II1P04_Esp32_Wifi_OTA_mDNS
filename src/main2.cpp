#include <Arduino.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <ArduinoOTA.h>
#include "wserial.h"

const char *ssid = "InovaIndustria";
const char *password = "industria50";
const char *hostName = "esp32name";

void test(std::string str){
  wserial::println(str.c_str());  
}

void setup() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(100);
  WiFi.setHostname(hostName);

  // Tenta listen até conseguir
  wserial::setup(115200, 47268UL);
  wserial::onInputReceived(test);
  wserial::println("[IP] is " + String(WiFi.localIP().toString()));

  if (!MDNS.begin(hostName)) wserial::println("[mDNS] begin failed");
  else wserial::println("[mDNS] begin in " + String(hostName));

  ArduinoOTA
      .onStart([]() {wserial::println("[OTA] Start");})
      .onEnd([]() {wserial::println("[OTA] End"); })
      .onProgress([](unsigned int p, unsigned int t) {wserial::println("[OTA] " + String((p*100)/t));})
      .onError([](ota_error_t e) { wserial::println("[OTA] Error " + String(e)); })
      .setHostname(hostName)
      .begin();
}



void loop() {
  ArduinoOTA.handle();
  wserial::loop();

  static float t = 0.0f;      // variável de tempo para a reta
  static uint32_t lastRetry2 = 0;
  if (millis() - lastRetry2 > 200) {
    lastRetry2 = millis();
    wserial::plot("reta",10*t);
    t += 0.2f;      // incrementa o tempo (ajuste a velocidade)
  }
}
