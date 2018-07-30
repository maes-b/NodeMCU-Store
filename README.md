# NodeMCU-Store

Control 2 Stores using the ESP8266 chip on NodeMCU

# Used Materials

 - NodeMCU with ESP8266 Chip
  ![NodeMCU](https://lh3.googleusercontent.com/uDWOs9wO_FhMBOA16CEyvQF6Uz1OdwqRAcuPnTRDpQ6dximdp8Cfl14gAjp_4OBgZnxLckgJZtAJ)

 - 2 x Dual Channels 5V Relays 
 ![Dual Channels 5V Relays](https://lh3.googleusercontent.com/vtX5tiV4JiMRewIamdKTO7vJwWhB8fnt8dmw53WZvUFkorQIx9n6-d9qCeoNW19gXUrsvwl7mR_q)
 
 - 2 x microswitch 
![MicroSwitch](https://lh3.googleusercontent.com/NkXL_XHidqQoCASYVPBLk1ChKYNsu7QWc_rlYx6Hlch8Xv9cnWcK0eWUFV6AN3zXDFGgt2oZL0Fz)


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


