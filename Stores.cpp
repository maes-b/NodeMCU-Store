
#include "Stores.h"


String Stores::splitString(String data, char separator, int index){
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

Stores::Stores(){}

void Stores::addStore(Store store){
  if(store.getId()%2!=0){
    _stores[0]=store;
  }else{
    _stores[1]=store;
  }
}

Store* Stores::getStores(){
  return _stores;
}

void Stores::setIpAdress(IPAddress ip){
  for(int index=0;index<2;index++){
    _stores[index].setIp(ip);
  }
}
String Stores::toJsonString(){
	DynamicJsonBuffer jsonBuffer(500);
  JsonObject& jsonEncoder = jsonBuffer.createObject();
  JsonArray& jsonStores = jsonEncoder.createNestedArray("stores");
  for(int index=0;index<2;index++){
  	JsonObject& jsonStore = jsonBuffer.createObject();
   	jsonStore["id"]=_stores[index].getId();
   	jsonStore["ipAdress"]=_stores[index].ipAdressToString();
   	jsonStore["state"]=_stores[index].stateToString();
   	jsonStore["room"]=_stores[index].getRoom();
   	jsonStore["type"]=_stores[index].typeToString();
  		
  	jsonStores.add(jsonStore);
  }

  return jsonEncoder["stores"];
}

JsonArray& Stores::allInformationJson(){
  DynamicJsonBuffer jsonBuffer(500);
  JsonObject& jsonEncoder = jsonBuffer.createObject();
  JsonArray& jsonStores = jsonEncoder.createNestedArray("stores");
  for(int index=0;index<2;index++){
    JsonObject& jsonStore = jsonBuffer.createObject();
    jsonStore["id"]=_stores[index].getId();
    jsonStore["ipAdress"]=_stores[index].ipAdressToString();
    jsonStore["pinUp"]=_stores[index].getPinUp();
    jsonStore["pinDown"]=_stores[index].getPinDown();
    jsonStore["pinEor"]=_stores[index].getPinSwitch();
    jsonStore["state"]=_stores[index].stateToString();
    jsonStore["room"]=_stores[index].getRoom();
    jsonStore["type"]=_stores[index].typeToString();
      
    jsonStores.add(jsonStore);
  }

  return jsonStores;
}

void Stores::doActionOnStores(Action action){
	for(int index=0;index<2;index++){
		_stores[index].doActionOnStore(action);
	}
}

void Stores::doActionOnStore(int id,Action action){
  _stores[id-1].doActionOnStore(action);
}

Action Stores::actionFromString(String action){
  if(action=="OPEN"){
    return O;
  }else if(action=="CLOSE"){
    return C;
  }else{
    return S;
  }
}

int Stores::updateStore(int id,String ipString,String state,String room,String type){
  IPAddress addr;
  if (addr.fromString(ipString)) {
    //check if String ip have format of IP addr
    String part01 = splitString(ipString,'.',0);
    String part02 = splitString(ipString,'.',1);
    String part03 = splitString(ipString,'.',2);
    String part04 = splitString(ipString,'.',3);    
    IPAddress ip(part01.toInt(),part02.toInt(),part03.toInt(),part04.toInt());
    Serial.print("Updated :");
    Serial.println(ip);
    setIpAdress(ip);
  }else{
    return 400;
  }
  
  if(_stores[id].stateToString()!=state){
    _stores[id].setState(_stores[id].stateFromString(state));    
  }
      
  if(_stores[id].getRoom()!=room){
    _stores[id].setRoom(room);  
  }

  if(_stores[id].typeToString()!=type){
    _stores[id].setType(_stores[id].typeFromString(type));  
  }
  return 200;
}

