

#include "Connectivity.h"

Connectivity::Connectivity(){}

void Connectivity::setupWifi(){
	int nbNetworks = WiFi.scanNetworks();
	String lastSsidTested ="";
	for (int index = 0; index < nbNetworks;index++) {//iterate over available Networks
		for (int connexion = 0; connexion<SIZEOF(_connexions);connexion++) {//iterate over known Network
	    	if(WiFi.SSID(index) == (_connexions[connexion]).ssid){//if it's one of our network try connection
		        Serial.print("Connecting to ");
	        	Serial.print(WiFi.SSID(index));
	        	lastSsidTested = (_connexions[connexion]).ssid;
	        	WiFi.begin((_connexions[connexion]).ssid, (_connexions[connexion]).password);	        
	        	break;
	      	}
	    }
	}
	
	while (WiFi.status() != WL_CONNECTED) {
		Serial.print(".");
	    delay(500);
	    digitalWrite(LED, LOW);
	    delay(500);
	    digitalWrite(LED, HIGH);
	}
	     
	Serial.print("\nWiFi connected to ");
	Serial.println(lastSsidTested);
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());
	digitalWrite(LED, HIGH);
	
	_stores.setIpAdress(WiFi.localIP());
}

void Connectivity::setupServer(){
	_server.on("/reboot",HTTP_GET,std::bind(&Connectivity::reboot,this));
  	_server.on("/store", HTTP_GET, std::bind(&Connectivity::handleActionOnStore,this));
  	_server.on("/store",HTTP_POST,std::bind(&Connectivity::handleUpdateOnStore,this));
  	_server.onNotFound(std::bind(&Connectivity::handleNotFound,this));

  	_server.begin(); //Start the server
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
			String ip = root["ipAdress"];
			String state = root["state"];
			String room = root["room"];
			String type = root["type"];

			int code = _stores.updateStore(id-1,ip,state,room,type);
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
