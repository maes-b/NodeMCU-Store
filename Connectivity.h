#ifndef Connectivity_h
#define Connectivity_h

#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include "Stores.h"
#define LED 16 /*LED PIN*/
#define APPLICATION_JSON "application/json"
#define SIZEOF(_array) (sizeof(_array) / sizeof(_array[0]))

typedef struct WifiConnexion{
  char* ssid;
  char* password;
}WifiConnexion;

class Connectivity{
public:
	Connectivity();

	WifiConnexion _connexions[2] = {{"SSID1","PASS1"},{"SSID1","PASS2"}};
	ESP8266WebServer _server = ESP8266WebServer(80);

	HTTPClient _client;
	
	Stores _stores = Stores(Store(1,WiFi.localIP(),4, 0,5, OPD, "DEFAULT", WINDOW),Store(2,WiFi.localIP(),14, 12,2, OPD, "DEFAULT", WINDOW));

	void setupWifi();
	void setupServer();
	void checkStoresState();
private:
	void handleActionOnStore();
	void handleUpdateOnStore();
	void handleNotFound();
	void reboot();
};

#endif
