# Movement Detection using ble

## Overview

The program does the following:

1. Scans for BLE devices using the BlueZ library.
2. Parses incoming BLE packets to extract accelerometer data.
3. Analyzes the accelerometer data to detect movement.
4. Outputs whether the tag is moving or stationary.

## Requirements

- Linux system with Bluetooth support
- BlueZ development libraries

## Installation

1. Install the BlueZ development libraries:
sudo apt-get install libbluetooth-dev

2. Compile the program:
gcc -o ble_accel_reader ble_accel_reader.c -lbluetooth -lm

The program will start scanning for BLE devices and output accelerometer data and movement status when it detects the appropriate BLE tag.

## Code Structure

- `main()`: Sets up Bluetooth scanning and processes incoming data.
- `parse_accel_data()`: Extracts accelerometer values from BLE packet data.
- `is_moving()`: Determines if the tag is moving based on changes in accelerometer data.
- `process_data()`: Handles parsed accelerometer data and outputs results.

## Notes

- The program is set to scan continuously. You may want to implement a mechanism to stop scanning after a certain time or on user input.
- The movement detection threshold may need adjustment based on your specific use case and the sensitivity of the accelerometer.
- This program requires root privileges to run due to its use of Bluetooth scanning.

## Future Improvements

- Implement more robust error handling.
- Add configuration options for scan duration and movement detection threshold.
- Improve power efficiency for long-term monitoring.
