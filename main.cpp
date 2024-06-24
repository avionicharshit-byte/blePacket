#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

#define BLE_SCAN_TIMEOUT 5 // Scan for 5 seconds

typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
} AccelData;

bool parse_accel_data(const uint8_t* data, size_t len, AccelData* accel_data) {
    if (len < 31 || data[0] != 0x02 || data[1] != 0x01 || data[2] != 0x06 || 
        data[3] != 0x03 || data[4] != 0x03 || data[5] != 0xE1 || data[6] != 0xFF) {
        return false;
    }

    accel_data->x = (int16_t)((data[20] << 8) | data[21]);
    accel_data->y = (int16_t)((data[22] << 8) | data[23]);
    accel_data->z = (int16_t)((data[24] << 8) | data[25]);

    return true;
}

bool is_moving(const AccelData* data, const AccelData* prev_data, float threshold) {
    float delta_x = data->x - prev_data->x;
    float delta_y = data->y - prev_data->y;
    float delta_z = data->z - prev_data->z;

    float magnitude = sqrt(delta_x*delta_x + delta_y*delta_y + delta_z*delta_z);

    return magnitude > threshold;
}

void process_data(uint8_t* data, size_t data_len) {
    static AccelData prev_data = {0};
    AccelData accel_data;

    if (parse_accel_data(data, data_len, &accel_data)) {
        printf("Accelerometer data: X=%d, Y=%d, Z=%d\n", accel_data.x, accel_data.y, accel_data.z);

        bool moving = is_moving(&accel_data, &prev_data, 10.0f);
        printf("Tag is %s\n", moving ? "moving" : "stationary");

        prev_data = accel_data;
    }
}

int main() {
    int device_id = hci_get_route(NULL);
    int device_handle = hci_open_dev(device_id);

    if (device_handle < 0) {
        perror("Failed to open HCI device");
        return 1;
    }

    uint8_t scan_type = 0x01;  // Active scanning
    uint8_t scan_filter = 0x00;  // Accept all advertising packets
    uint8_t filter_dup = 0x00;  // Do not filter duplicates

    if (hci_le_set_scan_parameters(device_handle, scan_type, htobs(0x0010), htobs(0x0010),
                                   scan_filter, filter_dup, BLE_SCAN_TIMEOUT) < 0) {
        perror("Failed to set scan parameters");
        hci_close_dev(device_handle);
        return 1;
    }

    if (hci_le_set_scan_enable(device_handle, 0x01, filter_dup, BLE_SCAN_TIMEOUT) < 0) {
        perror("Failed to enable scanning");
        hci_close_dev(device_handle);
        return 1;
    }

    printf("Scanning for BLE devices...\n");

    struct hci_filter old_filter, new_filter;
    socklen_t old_filter_len = sizeof(old_filter);
    getsockopt(device_handle, SOL_HCI, HCI_FILTER, &old_filter, &old_filter_len);

    hci_filter_clear(&new_filter);
    hci_filter_set_ptype(HCI_EVENT_PKT, &new_filter);
    hci_filter_set_event(EVT_LE_META_EVENT, &new_filter);
    setsockopt(device_handle, SOL_HCI, HCI_FILTER, &new_filter, sizeof(new_filter));

    uint8_t buf[HCI_MAX_EVENT_SIZE];
    evt_le_meta_event* meta_event;
    le_advertising_info* info;

    while (1) {
        int len = read(device_handle, buf, sizeof(buf));

        if (len < 0) {
            perror("Failed to read from HCI device");
            break;
        }

        if (buf[1] != EVT_LE_META_EVENT) {
            continue;
        }

        meta_event = (evt_le_meta_event*)(buf + HCI_EVENT_HDR_SIZE);

        if (meta_event->subevent != EVT_LE_ADVERTISING_REPORT) {
            continue;
        }

        info = (le_advertising_info*)(meta_event->data + 1);
        process_data(info->data, info->length);
    }

    setsockopt(device_handle, SOL_HCI, HCI_FILTER, &old_filter, sizeof(old_filter));

    if (hci_le_set_scan_enable(device_handle, 0x00, filter_dup, BLE_SCAN_TIMEOUT) < 0) {
        perror("Disable scanning failed");
    }

    hci_close_dev(device_handle);
    return 0;
}