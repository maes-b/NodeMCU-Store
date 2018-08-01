
#include "Connectivity.h"

Connectivity::Connectivity(){}

void Connectivity::setupWifi(){
  _connexions.addAP("ssid1", "pass1");   // add Wi-Fi networks you want to connect to
  _connexions.addAP("ssid2", "pass2");
  
  Serial.println("Connecting ...");
  while (_connexions.run() != WL_CONNECTED) { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
      Serial.print(".");
      delay(500);
      digitalWrite(LED, LOW);
      delay(500);
      digitalWrite(LED, HIGH);
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
  _server.on("/store", HTTP_GET, std::bind(&Connectivity::handleActionOnStore,this));
  _server.on("/store",HTTP_POST,std::bind(&Connectivity::handleUpdateOnStore,this));
  _server.onNotFound(std::bind(&Connectivity::handleNotFound,this));

  _server.begin(); //Start the server
  
}

void Connectivity::setupStores(){
  _stores.addStore(Store(1,WiFi.localIP(),4, 0,5, OPD, "1", WINDOW));
  _stores.addStore(Store(2,WiFi.localIP(),14, 12,2, OPD, "2", WINDOW));
  Serial.println("stores setup done");
}

void Connectivity::handleActionOnStore(){
	if(_server.args()==1 && _server.arg("action")!=""){
		String actionString = _server.arg("action");
		_stores.doActionOnStores(_stores.actionFromString(actionString));
    	_server.send ( 200, APPLICATION_JSON,"{\"code\":\"200\",\"message\":\"Command Sent\"}");
	}else if(_server.args()==2 && _server.arg("id")!="" && _server.arg("action")!=""){
		//only two params needed {id} and {action}
		//url : store?id={id}&action={action}
		String idString = _server.arg("id");
		if(idString.toInt()>0){
			String actionString = _server.arg("action");
			_stores.doActionOnStore(idString.toInt(),_stores.actionFromString(actionString));
    		_server.send ( 200, APPLICATION_JSON,"{\"code\":\"200\",\"message\":\"Command Sent\"}");
    	}else{
    		_server.send(409, APPLICATION_JSON,"{\"code\":\"409\",\"message\":\"Bad Request : Request parameter {id} is not valid\"}" );
    	}
  	}else if(_server.args()==0){
	    _server.send ( 200,APPLICATION_JSON,_stores.toJsonString());
  	}else{
  		_server.send(409, APPLICATION_JSON,"{\"code\":\"409\",\"message\":\"Bad Request\"}" );
  	}
}

void Connectivity::handleUpdateOnStore(){
	if (_server.hasArg("plain")!= false){ //Check if body received
		DynamicJsonBuffer jsonBuffer(500);
		JsonObject& root = jsonBuffer.parseObject(_server.arg("plain"));

		int id = root["id"];
		if(id==1 || id==2){
			String state = root["state"];
			String room = root["room"];
			String type = root["type"];

			int code = _stores.updateStore(id-1,state,room,type);
		}else{
			_server.send(409, APPLICATION_JSON,"{\"code\":\"409\",\"message\":\"Bad Request : Request body parameter {id} is not valid\"}" );		
		}
		_server.send(200,APPLICATION_JSON,"{\"code\":\"200\",\"message\":\"Updated\"}");
    }
 	_server.send(409, APPLICATION_JSON,"{\"code\":\"409\",\"message\":\"Bad Request : Request Body not found\"}" );
}

void Connectivity::handleNotFound(){
	_server.send(404, APPLICATION_JSON,"{\"code\":\"404\",\"message\":\"Page doesn't exist\"}" );
}

void Connectivity::reboot(){
	_server.send(200,APPLICATION_JSON,"{\"code\":\"200\",\"message\":\"Restart Command Sent\"}");
  	ESP.reset();//worked only if you reset manually one time NodeMCU after flash
}

void Connectivity::checkStoresState(){
	for(int index=0;index<2;index++){
    if((_stores.getStores())[index].getSwitchState()==LOW && (_stores.getStores())[index].getState()==CLG){
      (_stores.getStores())[index].doActionOnStore(S);//stop relay
      (_stores.getStores())[index].setState(CLD);//set state to CLOSED

      //TODO : notify that store is closed
      //_client.begin("url");
      //_client.addHeader("");
      //int code = _client.POST("message");
      //String response = http.getString();
      //_client.end();
    }
  }
}
