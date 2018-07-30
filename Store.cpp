
#include "Store.h"

Store::Store(){}

Store::Store(int id,IPAddress ip,byte up,byte down,byte swh,State state,String room,Type type):
_id(id),_ip(ip),_state(state),_room(room),_type(type),_up(up),_down(down),_switch(swh)
{
  pinMode(_up,OUTPUT);
  pinMode(_down,OUTPUT);
  pinMode(_switch,INPUT_PULLUP);
  digitalWrite(_up,HIGH);
  digitalWrite(_down,HIGH);
}

int Store::getId(){return _id;}

void Store::setId(int id){_id=id;}
	
IPAddress Store::getIp(){return _ip;}

void Store::setIp(IPAddress ip){_ip=ip;}
	
byte Store::getPinUp(){return _up;}

void Store::setPinUp(byte pin){_up=pin;}

byte Store::getPinDown(){return _down;}

void Store::setPinDown(byte pin){_down=pin;}

byte Store::getPinSwitch(){return _switch;}

void Store::setPinSwitch(byte pin){_switch=pin;}

State Store::getState(){return _state;}

void Store::setState(State state){_state=state;}

String Store::getRoom(){return _room;}

void Store::setRoom(String room){_room=room;}

Type Store::getType(){return _type;}

void Store::setType(Type type){_type= type;}

String Store::ipAdressToString(){
	return String(_ip[0]) + String(".") +
	String(_ip[1]) + String(".") +
	String(_ip[2]) + String(".") +
	String(_ip[3])  ;
}

String Store::stateToString(){
	switch(_state){
    	case OPD: return "OPEN";
    	case OPG: return "OPENING";
    	case CLD: return "CLOSED";
    	case CLG: return "CLOSING";
    	case STD: 
    	default: return "STOPPED";
	}
}

String Store::typeToString(){return _type == WINDOW ? "WINDOW" : "DOOR";}

State Store::stateFromString(String state){
  if(state=="OPEN"){return OPD;}
  else if(state=="OPENING"){return OPG;}
  else if(state=="CLOSED"){return CLD;}
  else if(state=="CLOSING"){return CLG;}
  else{return STD;}
}

Type Store::typeFromString(String type){
  return type == "WINDOW" ? WINDOW : DOOR;
}

int Store::doActionOnStore(Action action){
	switch(action){
		case O:
			digitalWrite(_down, HIGH);
			digitalWrite(_up, LOW);
      _state = OPG;
      return 0;
    case C:
      digitalWrite(_down, LOW);
      digitalWrite(_up, HIGH);
      _state = CLG;
      return 0;
    case S:
    default:
      digitalWrite(_down, HIGH);
      digitalWrite(_up, HIGH);
      _state = STD;
      return 0;
	}
}

int Store::getSwitchState(){
  return digitalRead(_switch);
}
