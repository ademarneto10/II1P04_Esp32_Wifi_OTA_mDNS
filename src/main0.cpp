#include <WiFi.h>
#include <ESPmDNS.h>
#include "wserial.h"

void setup() {
  WiFi.begin("InovaIndustria","industria50");
  while (WiFi.status()!=WL_CONNECTED) delay(100);

    // Tenta listen até conseguir
  wserial::setup(115200, 47268UL);
  wserial::println("[IP] is " + String(WiFi.localIP().toString()));

  MDNS.begin("esp32name");          // acessa em esp32name.local
}
void loop() {
    wserial::loop();
}
