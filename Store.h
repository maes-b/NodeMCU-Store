#ifndef Store_h
#define Store_h

#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

#define LED 16 /*LED PIN*/
typedef enum Type {WINDOW,DOOR} Type;
typedef enum State {OPD=1,OPG=2,CLD=3,CLG=4,STD=5} State;//OPD OPENED , OPG OPENING,CLD CLOSED,CLG CLOSING,STD STOPED
typedef enum Action {O,C,S} Action;//O OPEN , C CLOSE , S STOP

class Store{
private:
	int _id;
	IPAddress _ip;
	byte _up;
	byte _down;
	byte _switch;
	State _state;
	String _room;
	Type _type;
public:
	Store();
	Store(int id,IPAddress ip,byte up,byte down,byte swh,State state,String room,Type type);

	int getId();
	void setId(int id);
	
	IPAddress getIp();
	void setIp(IPAddress ip);
	
	byte getPinUp();
	void setPinUp(byte pin);

	byte getPinDown();
	void setPinDown(byte pin);

	byte getPinSwitch();
	void setPinSwitch(byte pin);
	int getSwitchState();

	State getState();
	void setState(State state);

	String getRoom();
	void setRoom(String room);

	Type getType();
	void setType(Type type);

	int doActionOnStore(Action action);
  	String ipAdressToString();
  	String stateToString();
  	String typeToString();
  	State stateFromString(String state);
  	Type typeFromString(String type);
};

#endif
