# NodeMCU-Store

Control 2 Stores using the ESP8266 chip on NodeMCU

# Used Materials

 - NodeMCU with ESP8266 Chip
  ![NodeMCU](https://lh3.googleusercontent.com/OjmrEXp4pqTkyDDJsvaNHeD6rue5_fMiKTAmxfrZ9ddvz5TbRQf0LYJlXmWJZOKDWAuW3mdF2lfRPdPMXkYANaVAEzXJZFuYWnkrvdi85G23tPDl3EdynUSPICTRKoaZZD296-gbyA=w2400)

 - 2 x Dual Channels 5V Relays 
 ![Dual Channels 5V Relays](https://lh3.googleusercontent.com/jQplh4g4A_EalNVIx69ULZxjdyOjp3Hqscu7Zir55UaHwIch_1yCRK5eGvhZ5fw2avCDmxdz4OIjabcBalEucf5SLqobBy2iV7jwEnlbVH9VFqo4YtNMcRWW2lCOkNYeyKmSukn0iw=s150-p-k)
 
 - 2 x microswitch 
![MicroSwitch](https://lh3.googleusercontent.com/buBnuqHtO9A2mQy4RDfMcwMaQ_p0-O2ADUQToGA0SUH4iE0sInXRc3cjxCs6sWrQFbEQaGbHDMHrFVmxyT3TVGXVkssocDanVTPZsM7uJ_r-FBzXGPwKHGiuCiklE8sFV7yoYgHuJg=s100-p-k)


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


