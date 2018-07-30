#ifndef Stores_h
#define Stores_h

#include "Store.h"

class Stores{
private:
	Store _stores[2];//one nodeMCU handle 2 stores max
public:
	Stores(Store store1, Store store2);
  Store* getStores();
	String toJsonString();
    void setIpAdress(IPAddress ip);
	void doActionOnStores(Action action);
	void doActionOnStore(int id,Action action);
	Action actionFromString(String action);
	int updateStore(int id,String ip,String state,String room,String type);//change info on store
  
};

#endif
