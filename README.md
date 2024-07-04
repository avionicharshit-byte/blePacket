**Bluetooth Packet Analyzer**

**Overview:**
This program analyzes Bluetooth Low Energy (BLE) advertising packets to identify and extract information from Eddystone (Accelerometer) and iBeacon packets. 
It prints details such as MAC addresses, accelerometer data, RSSI values, and movement status.

**Features**
- Parses BLE advertising packets to determine packet type (Eddystone or iBeacon).
- Extracts MAC addresses and specific data fields from recognized packet types.
- Identifies accelerometer readings and determines if the tag is moving based on data values.

**Usage**
Example Packets:
- Predefined packets are provided in the main function.
- These packets simulate BLE advertising data and demonstrate the program's capability to interpret Eddystone and iBeacon packets.

**User Input:**
- Users can input their own BLE advertising packet during program execution.
- Enter the packet in hexadecimal format (e.g., 0x0201061AFF4C00021553594F4F4B534F4349414C444953544500000000E8).
- For Execution - Try this link - https://replit.com/@avionicharshit/blePacketAnalyzer  or Copy the code from main.c and run on this online ide - https://www.programiz.com/c-programming/online-compiler/
- Code Execution ss
- ![image](https://github.com/avionicharshit-byte/blePacket/assets/78672319/0c1b0e93-2043-46b0-8fd8-7c466ccdea5d)





