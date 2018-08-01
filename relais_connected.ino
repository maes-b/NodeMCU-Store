
#define LED 16 /*LED PIN*/
#define APPLICATION_JSON "application/json"
#define SIZEOF(_array) (sizeof(_array) / sizeof(_array[0]))

#include "Connectivity.h"

/**
 * PIN RELAY UP STORE 1 : GPIO 4 / D2
 * PIN RELAY DOWN STORE 1 : GPIO 0 / D3
 * PIN SWITCH DOWN 1 : GPIO 5 / D1
 * 
 * PIN RELAY UP STORE 2 : GPIO 14 / D5
 * PIN RELAY DOWN STORE 2 : GPIO 12 / D6
 * PIN SWITCH DOWN 2 : GPIO 2 / D4
 * 
 */
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



