# NodeMCU-Store

Control 2 Stores using the ESP8266 chip on NodeMCU

# Used Materials

 - NodeMCU with ESP8266 Chip
  ![NodeMCU](https://photos.app.goo.gl/ekprfzfcLh7uRGU48)

 - 2 x Dual Channels 5V Relays 
 ![Dual Channels 5V Relays](https://photos.app.goo.gl/yinAraVvASfY7No69)
 
 - 2 x microswitch 
![MicroSwitch](https://photos.app.goo.gl/c99boWD7Rt4LhNSC9)


# How to use

## 1 - Setup wifi

Just set your WIFI SSIDs and Passwords in the file "Connectivity.h" at line 22

## 2 - Push firmware to your node MCU

Just Compile and push firmware to your nodeMCU ship

## 3 - Connect relays and switches

Use these GPIO/PIN :
-	Store 1 : 
	-  PIN UP : GPIO 4 / D2
	-  PIN DOWN : GPIO 0 / D3
    -  PIN End-Of-Run Switch : GPIO 5 / D1
- Store 2 : 
	-	PIN UP : GPIO 14 / D5
	-	PIN DOWN : GPIO 12 / D6
	-	PIN SWITCH : GPIO 2 / D4
	
## 4 - Enjoy
	Available HTTP Request:
		GET 	{ip}/store?id={id}action={ACTION*} -> close store by id
		GET 	{ip}/store?action={ACTION*} -> do an action on both stores
		GET		{ip}/store -> get information about stores
		POST 	{ip}/store -> update information on store
			exemple to update store 1 use this body request:
			{"id": 1,"ipAdress": "192.168.0.29","state": "CLOSED","room": "TV Room","type": "WINDOW"}
	
	*ACTION = OPEN,CLOSE or STOP
	
	NB1: All request response are in JSON
	NB2: All change made on store informations are lost if NodeMCU is rebooted


