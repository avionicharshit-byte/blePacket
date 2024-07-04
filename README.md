Packet Analysis Program
This C program (packet_analysis.c) demonstrates how to parse and analyze Bluetooth Low Energy (BLE) packets, specifically focusing on Eddystone and iBeacon formats. It prints information about each packet type, including the MAC address and relevant data.

Features
Parses BLE packets formatted as Eddystone (Accelerometer) and iBeacon.
Extracts MAC address and specific data fields from each packet.
Determines if the detected tag is moving or stationary based on accelerometer data.
Requirements
To compile and run this program, you need:

A C compiler (e.g., GCC)
Standard C libraries (stdio.h, stdlib.h, string.h, stdint.h)
How to Use
Compilation:

Open a terminal and navigate to the directory containing packet_analysis.c.
Compile the program using GCC:
bash
Copy code
gcc packet_analysis.c -o packet_analysis
Execution:

Run the compiled executable:
bash
Copy code
./packet_analysis
Example Output:

The program processes predefined example packets and prompts the user to input a custom packet.
It prints details about each packet type, including the type of packet (Eddystone or iBeacon), MAC address, RSSI (for iBeacon), and accelerometer data (for Eddystone).
Custom Input:

After processing example packets, the program waits for user input to analyze a custom packet.
Input a BLE packet in hexadecimal format (e.g., 0x0201060303E1FF1216E1FFA10364FFF4000FFF003772A33F23AC).
Packet Format:

Ensure the packet follows the expected format:
Eddystone (Accelerometer): Starts with 0x0201060303E1FF followed by specific data fields.
iBeacon: Starts with 0x0201061AFF4C000215 followed by specific data fields.
Output Interpretation:

The program identifies the type of BLE packet based on its structure and prints relevant information.
For Eddystone packets, it decodes accelerometer data and determines if the tag is moving or stationary.
For iBeacon packets, it extracts RSSI values as an indication of signal strength.
Example Packets
Predefined example packets are included in the main() function of the code. These packets demonstrate different BLE formats and their parsing by the program.
- For Execution - Try this link - https://replit.com/@avionicharshit/blePacketAnalyzer
- Code Execution ss
- ![image](https://github.com/avionicharshit-byte/blePacket/assets/78672319/0c1b0e93-2043-46b0-8fd8-7c466ccdea5d)





