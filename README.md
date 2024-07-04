Bluetooth Packet Analyzer
Overview
This C program is designed to analyze Bluetooth Low Energy (BLE) packets, extracting specific information from Eddystone (Accelerometer) and iBeacon packet formats. It parses hexadecimal packet data and provides insights into device movement (accelerometer data) and signal strength (RSSI).

Features
Packet Types Supported:

Eddystone (Accelerometer): Detects BLE packets indicating device movement using accelerometer data.
iBeacon: Identifies BLE advertising packets and extracts the received signal strength indicator (RSSI).
Functionality:

Parses and interprets BLE packet data in hexadecimal format.
Identifies packet type based on predefined header values.
Extracts and displays MAC addresses, accelerometer readings (x, y, z), and RSSI values.
Supports both predefined example packets and user-input custom packets for analysis.
Usage
Example Packets:

Includes predefined BLE packets for demonstration purposes.
Demonstrates how the program identifies and interprets different BLE packet types.
Input Your Own Packet:

Allows users to input a custom BLE packet in hexadecimal format.
Outputs detailed information about the packet type, MAC address, accelerometer data (if applicable), and RSSI.
- For Execution - Try this link - https://replit.com/@avionicharshit/blePacketAnalyzer
- Code Execution ss
- ![image](https://github.com/avionicharshit-byte/blePacket/assets/78672319/0c1b0e93-2043-46b0-8fd8-7c466ccdea5d)





