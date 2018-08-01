#ifndef Stores_h
#define Stores_h

#include "Store.h"

class Stores{
private:
	Store _stores[2];//one nodeMCU handle 2 stores max
public:
	Stores();
  void addStore(Store store);
  Store* getStores();
	String toJsonString();
  void setIpAdress(IPAddress ip);
	void doActionOnStores(Action action);
	void doActionOnStore(int id,Action action);
	Action actionFromString(String action);
	int updateStore(int id,String state,String room,String type);//change info on store
  
};

#endif
