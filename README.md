BLE Packet Analysis
This C program parses and analyzes Bluetooth Low Energy (BLE) packets, specifically focusing on Eddystone (Accelerometer) and iBeacon formats. It prints packet information including type, MAC address, and additional data fields.

Features
Parses BLE packets formatted as Eddystone (Accelerometer) and iBeacon.
Extracts MAC address and specific data fields.
Determines if the tag is moving or stationary based on accelerometer data.
Handles predefined example packets and user-input packets.
Usage
Compilation:

Compile the program using GCC or any C compiler:
bash
Copy code
gcc packet_analysis.c -o packet_analysis
Execution:

Run the compiled executable:
bash
Copy code
./packet_analysis
Input:

After processing example packets, input a custom BLE packet in hexadecimal format when prompted.
Output:

The program prints details about each packet type, including whether the tag is moving or stationary for Eddystone packets, and RSSI for iBeacon packets.
Example
Example packets are included in the code (main() function) for demonstration purposes.
- For Execution - Try this link - https://replit.com/@avionicharshit/blePacketAnalyzer
- Code Execution ss
- ![image](https://github.com/avionicharshit-byte/blePacket/assets/78672319/0c1b0e93-2043-46b0-8fd8-7c466ccdea5d)





