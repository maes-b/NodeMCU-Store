
#define LED 16 /*LED PIN*/
#define APPLICATION_JSON "application/json"
#define SIZEOF(_array) (sizeof(_array) / sizeof(_array[0]))

#include "Connectivity.h"

Connectivity connectivity;

void setup() {
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
  digitalWrite(LED, HIGH);
  connectivity.setupWifi();
  connectivity.setupServer();
  connectivity.setupStores();
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    connectivity._server.handleClient();
    connectivity.checkStoresState();
   
  } else {
    Serial.println("\nWIFI Connexion lost");
    ESP.reset();//worked only if you reset one time manually NodeMCU after flash
  }
}



