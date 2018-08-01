#ifndef Connectivity_h
#define Connectivity_h

#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include "Stores.h"

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
  HTTPClient _client;
private:
  ESP8266WiFiMulti _connexions;
  
  Stores _stores;
	
	void handleActionOnStore();
	void handleUpdateOnStore();
	void handleNotFound();
	void reboot();
 
};

#endif
