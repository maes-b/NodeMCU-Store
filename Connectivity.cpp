
#include "Connectivity.h"

Connectivity::Connectivity(){}

void Connectivity::setupWifi(){
  _connexions.addAP(SSID1, PASS1);   // add Wi-Fi networks you want to connect to
  _connexions.addAP(SSID2, PASS2);
  
  Serial.println("Connecting ...");
  while (_connexions.run() != WL_CONNECTED) { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
      Serial.print(".");
      delay(500);
      digitalWrite(LED, LOW);
      delay(500);
      digitalWrite(LED, HIGH);
  }
  if(WiFi.SSID()==SSID1){
    IPAddress _IP(192, 168, 0, ESP_ADDR);
    IPAddress _GATEWAY(192, 168, 0, 254);
    IPAddress _SUBNET(255, 255, 255, 0);
    WiFi.config(_IP,_GATEWAY,_SUBNET);
  }
  Serial.print("\nWiFi connected to ");
  Serial.println(WiFi.SSID());
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
	_stores.setIpAdress(WiFi.localIP());
  
  digitalWrite(LED, HIGH);
}

void Connectivity::setupServer(){
  _server.on("/reboot",HTTP_GET,std::bind(&Connectivity::reboot,this));
  _server.on("/Stores", HTTP_GET, std::bind(&Connectivity::handleActionOnStore,this));
  _server.on("/Stores",HTTP_POST,std::bind(&Connectivity::handleUpdateOnStore,this));
  _server.on("/",HTTP_GET,std::bind(&Connectivity::handleRoot,this));
  _server.onNotFound(std::bind(&Connectivity::handleNotFound,this));
  
  _server.begin(); //Start the server
}

void Connectivity::setupStores(){
  _stores.addStore(STORE1);
  _stores.addStore(STORE2);
  Serial.println("stores setup done");
}

void Connectivity::handleActionOnStore(){
  if(_server.args()==1 && _server.arg("action")!=""){
    String actionString = _server.arg("action");
		_stores.doActionOnStores(_stores.actionFromString(actionString));
    sendMessage(200,"Command Sent");
	}else if(_server.args()==2 && _server.arg("id")!="" && _server.arg("action")!=""){
		//only two params needed {id} and {action}
		//url : store?id={id}&action={action}
		String idString = _server.arg("id");
		if(idString.toInt()>0){
			String actionString = _server.arg("action");
			_stores.doActionOnStore(idString.toInt(),_stores.actionFromString(actionString));
    	sendMessage(200,"Command Sent");
    }else{
       sendMessage(409,"Bad Request : Request parameter {id} is not valid");
    }
  }else if(_server.args()==0){
	   _server.send(200,APPLICATION_JSON,_stores.toJsonString());
  }else{
     sendMessage(409,"Bad Request");
  }
}

void Connectivity::handleUpdateOnStore(){
	if (_server.hasArg("plain")!= false){ //Check if body received
		DynamicJsonBuffer jsonBuffer(500);
		JsonObject& root = jsonBuffer.parseObject(_server.arg("plain"));

		int id = root["id"];
		if(id==1 || id==2){
      String ip = root["ipAdress"];
			String state = root["state"];
			String room = root["room"];
			String type = root["type"];    
			int code = _stores.updateStore(id-1,ip,state,room,type);
      if(code==200){
        if(WiFi.localIP() != _stores.getStores()[id-1].getIp()){
          _server.send(200,APPLICATION_JSON,_server.arg("plain"));
          delay(1000);
          IPAddress gateway(192, 168, 0, 254);
          IPAddress subnet(255, 255, 255, 0);
          WiFi.config(_stores.getStores()[id-1].getIp(),gateway,subnet);
        }else{
          _server.send(200,APPLICATION_JSON,_server.arg("plain"));
        }
      }else{
        sendMessage(422,"Not Updated");    
      }
		}else{
      sendMessage(409,"Bad Request : Request body parameter {id} is not valid");		
		}
  }
  sendMessage(409,"Bad Request : Request Body not found");
}

void Connectivity::handleNotFound(){
  sendMessage(404,"Page doesn't exist");
}

void Connectivity::reboot(){
  sendMessage(200,"Reboot command sent");
  ESP.reset();//worked only if you reset manually one time NodeMCU after flash
}

void Connectivity::handleRoot(){
  DynamicJsonBuffer jsonBuffer(500);
  JsonObject& jsonEncoder = jsonBuffer.createObject();
  jsonEncoder["version"]=FIRMWARE_VERSION;
  jsonEncoder["stores"] = _stores.allInformationJson();
  String message;
  jsonEncoder.printTo(message);
  _server.send(200,APPLICATION_JSON,message);
}

void Connectivity::checkStoresState(){
	for(int index=0;index<2;index++){
    if((_stores.getStores())[index].getSwitchState()==LOW && (_stores.getStores())[index].getState()==CLG){
      (_stores.getStores())[index].doActionOnStore(S);//stop relay
      (_stores.getStores())[index].setState(CLD);//set state to CLOSED
  
      String url = String(SERVER_ADDR)+"/api/Stores/";
      String json = (_stores.getStores())[index].toJsonString();
     
     HTTPClient _client;
     _client.begin(url);
     _client.addHeader("Content-Type", APPLICATION_JSON);
     _client.POST(json);
     _client.writeToStream(&Serial);
     _client.end();
    }
  }
}

void Connectivity::sendMessage(int code, String message){
  DynamicJsonBuffer jsonBuffer(500);
  JsonObject& jsonEncoder = jsonBuffer.createObject();
  jsonEncoder["code"]=code;
  jsonEncoder["message"]=message;

  String json;
  jsonEncoder.printTo(json);
  _server.send(code,APPLICATION_JSON,json);
}

