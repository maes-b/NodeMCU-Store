
#include "Stores.h"


String getValue(String data, char separator, int index){
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

int Stores::updateStore(int id,String state,String room,String type){
  if(_stores[id].stateToString()!=state){
    _stores[id].setState(_stores[id].stateFromString(state));    
  }
      
  if(_stores[id].getRoom()!=room){
    _stores[id].setRoom(room);  
  }

  if(_stores[id].typeToString()!=type){
    _stores[id].setType(_stores[id].typeFromString(type));  
  }
}

