#ifndef Connectivity_h
#define Connectivity_h

#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h> 
#include <ESP8266HTTPClient.h>
#include <ESP8266mDNS.h>   
#include <ArduinoJson.h>
#include "Stores.h"

#define FIRMWARE_VERSION "3.0.0"

#define ESP_ADDR 102

#define SERVER_ADDR "http://addr"

#define SSID1 "SSID1"
#define PASS1 "PASS1"

#define SSID2 "SSID2"
#define PASS2 "PASS2"

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
#define STORE1 Store(1,WiFi.localIP(),4, 0,5, OPD, "1", WINDOW)
#define STORE2 Store(2,WiFi.localIP(),14, 12,2, OPD, "2", WINDOW)

#define LED 16 /*LED PIN*/
#define APPLICATION_JSON "application/json"
#define SIZEOF(_array) (sizeof(_array) / sizeof(_array[0]))

class Connectivity{
public:
	Connectivity();
	void setupWifi();
	void setupServer();
  void setupStores();
	void checkStoresState();
  ESP8266WebServer _server = ESP8266WebServer(80);
private:
  ESP8266WiFiMulti _connexions;
  
  Stores _stores;
	
	void handleActionOnStore();
	void handleUpdateOnStore();
	void handleNotFound();
  void handleRoot();
	void reboot();
  void sendMessage(int code, String message);
 
};
#endif
