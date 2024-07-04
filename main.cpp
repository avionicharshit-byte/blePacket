#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define ACC_DATA_INDEX 13
#define ACC_DATA_LENGTH 6
#define MAC_ADDRESS_LENGTH 6
#define RSSI_INDEX 31
#define MAX_PACKET_LENGTH 100

typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
} AccelerometerData;

AccelerometerData parse_accelerometer_data(const char *hex_string) {
    AccelerometerData acc_data;
    unsigned int bytes[ACC_DATA_LENGTH];
    
    for (int i = 0; i < ACC_DATA_LENGTH; i++) {
        sscanf(hex_string + ACC_DATA_INDEX*2 + i*2, "%2x", &bytes[i]);
    }
    
    acc_data.x = (bytes[1] << 8) | bytes[0];
    acc_data.y = (bytes[3] << 8) | bytes[2];
    acc_data.z = (bytes[5] << 8) | bytes[4];
    
    return acc_data;
}

void parse_mac_address(const char *hex_string, char *mac_address) {
    unsigned int bytes[MAC_ADDRESS_LENGTH];
    
    for (int i = 0; i < MAC_ADDRESS_LENGTH; i++) {
        sscanf(hex_string + i*2, "%2x", &bytes[i]);
    }
    
    sprintf(mac_address, "%02X:%02X:%02X:%02X:%02X:%02X", 
            bytes[0], bytes[1], bytes[2], bytes[3], bytes[4], bytes[5]);
}

int8_t parse_rssi(const char *hex_string) {
    unsigned int rssi;
    sscanf(hex_string + RSSI_INDEX*2, "%2x", &rssi);
    return (int8_t)rssi - 256;
}

bool is_moving(AccelerometerData acc_data) {
    float threshold = 500.0; // Adjust this threshold as needed
    float magnitude = sqrt(acc_data.x*acc_data.x + acc_data.y*acc_data.y + acc_data.z*acc_data.z);
    return magnitude > threshold;
}

void process_packet(const char *packet) {
    char mac_address[18];
    AccelerometerData acc_data = parse_accelerometer_data(packet);
    parse_mac_address(packet, mac_address);
    int8_t rssi = parse_rssi(packet);
    
    float magnitude = sqrt(acc_data.x*acc_data.x + acc_data.y*acc_data.y + acc_data.z*acc_data.z);
    
    printf("Packet: %s\n", packet);
    printf("MAC Address: %s\n", mac_address);
    printf("RSSI: %d dBm\n", rssi);
    printf("Accelerometer Data: X: %d, Y: %d, Z: %d\n", acc_data.x, acc_data.y, acc_data.z);
    printf("Acceleration Magnitude: %.2f\n", magnitude);
    printf("Tag status: %s\n\n", is_moving(acc_data) ? "Moving" : "Stationary");
}

int main() {
    const char *packet1 = "0201060303E1FF1216E1FFA10364FFF4000FFF003772A33F23ACB4";
    const char *packet2 = "0201060303E1FF1216E1FF010002000300FF003772A33F23ACC8";
    char user_packet[MAX_PACKET_LENGTH];

    printf("Processing Packet 1:\n");
    process_packet(packet1);
    
    printf("Processing Packet 2:\n");
    process_packet(packet2);
    
    printf("Enter your own packet (hexadecimal format, max %d characters):\n", MAX_PACKET_LENGTH - 1);
    if (fgets(user_packet, sizeof(user_packet), stdin) != NULL) {
       
        user_packet[strcspn(user_packet, "\n")] = 0;
        
        printf("\nProcessing User's Packet:\n");
        process_packet(user_packet);
    } else {
        printf("Error reading input.\n");
    }
    
    return 0;
}
