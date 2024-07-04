#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// Function to print packet information
void print_packet_info(const char* packet) {
    // Skip the "0x" prefix
    packet += 2;

    // Convert packet string to byte array
    int len = strlen(packet) / 2;
    unsigned char data[len];
    for (int i = 0; i < len; i++) {
        sscanf(packet + 2 * i, "%2hhx", &data[i]);
    }

    // Check for Eddystone (Accelerometer)
    if (len >= 18 && data[5] == 0xE1 && data[6] == 0xFF) {
        // Extract MAC address (last 6 bytes)
        printf("Packet Type: Eddystone (Accelerometer)\n");
        printf("MAC Address: ");
        for (int i = len - 6; i < len; i++) {
            printf("%02X", data[i]);
            if (i < len - 1) {
                printf(":");
            }
        }
        printf("\n");

        // Extract accelerometer data
        int16_t x = (data[12] << 8) | data[13];
        int16_t y = (data[14] << 8) | data[15];
        int16_t z = (data[16] << 8) | data[17];

        printf("Accelerometer X: %d\n", x);
        printf("Accelerometer Y: %d\n", y);
        printf("Accelerometer Z: %d\n", z);

        // Determine if the tag is moving
        if (x != 0 || y != 0 || z != 0) {
            printf("Tag is moving\n");
        } else {
            printf("Tag is stationary\n");
        }
    }
    // Check for iBeacon
    else if (len >= 30 && data[5] == 0x4C && data[6] == 0x00) {
        // Extract MAC address (last 6 bytes)
        printf("Packet Type: iBeacon\n");
        printf("MAC Address: ");
        for (int i = len - 6; i < len; i++) {
            printf("%02X", data[i]);
            if (i < len - 1) {
                printf(":");
            }
        }
        printf("\n");

        // Extract RSSI value (last byte)
        int8_t rssi = data[len - 1];
        printf("RSSI: %d\n", rssi);
    } else {
        printf("Unknown packet type\n");
    }
}

int main() {
    // Example packets
    const char* packets[] = {
        "0x0201060303E1FF1216E1FFA10364FFF4000FFF003772A33F23AC",
        "0x0201061AFF4C00021553594F4F4B534F4349414C444953544500000000E8",
        "0x0201060303E1FF1216E1FFA10364FFF60011FF003772A33F23AC"

      // Packets user can give 
     // 0x0201061AFF4C00021553594F4F4B534F4349414C444953544500000000E8
    //  0x0201060303E1FF1216E1FFA10364FFF40011FF033772A33F23AC
   //   0x0201061AFF4C00021553594F4F4B534F4349414C444953544500000000E8

    };

    printf("Processing example packets:\n\n");
    for (int i = 0; i < sizeof(packets) / sizeof(packets[0]); i++) {
        print_packet_info(packets[i]);
        printf("\n");
    }

    // Allow user to input their own packet
    char user_packet[100];
    printf("Enter your own packet: ");
    scanf("%s", user_packet);

    printf("Processing user packet:\n\n");
    print_packet_info(user_packet);

    return 0;
}
