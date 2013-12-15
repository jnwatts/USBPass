#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "usbpass_private.h"

USBPass_private::USBPass_private() :
    serial(),
    name(),
    device(NULL)
{
}

#define MIN(a,b) ((a < b)?(a):(b))

void USBPass_private::get_name()
{
    this->name = "";
    if (this->serial.size() == 0)
        return;
    bool wasOpen = true;
    if (this->device == NULL) {
        wasOpen = false;
        std::wstring wserial(this->serial.begin(), this->serial.end());
        this->device = hid_open(USBPASS_VID, USBPASS_PID, wserial.c_str());
    }
    //TODO: Figure out how to request name?
    if (!wasOpen) {
        hid_close(this->device);
        device = NULL;
    }
}

void USBPass_private::send_report_string(uint8_t id, std::string str)
{
    send_large_block(id, str.c_str(), str.length());
}

void USBPass_private::send_report_byte(uint8_t id, char value)
{
    send_report(id, &value, sizeof(value));
}

void USBPass_private::send_large_block(uint8_t id, const char *buf, int buf_len)
{
    if (this->device) {
        int result = 0;
        uint8_t chunk_offset = 0;
        uint8_t chunk_len = 0;
        uint8_t report_buf[REPORT_MAX_LENGTH];
        while (buf_len > 0) {
            int report_len = 0;
            chunk_len = MIN(buf_len, REPORT_MAX_LENGTH - 3);
            report_buf[report_len++] = id;
            report_buf[report_len++] = chunk_offset;
            report_buf[report_len++] = chunk_len;
            memcpy(&report_buf[report_len], buf + chunk_offset, chunk_len);
            result = hid_send_feature_report(this->device, report_buf, report_len);
            if (result < 0) {
                perror("Failed to send feature report");
                return;
            }
            chunk_offset += chunk_len;
        }
    }
}

void USBPass_private::send_report(uint8_t id, const char *buf, int buf_len)
{
    if (this->device) {
        uint8_t report_buf[REPORT_MAX_LENGTH];
        int report_len = 0;
        int result = 0;
        report_buf[report_len++] = id;
        if (buf != NULL && buf_len >= 1) {
            int len = MIN(buf_len, REPORT_MAX_LENGTH - 1);
            memcpy(&report_buf[report_len], buf, len);
            report_len += len;
        }
        result = hid_send_feature_report(this->device, report_buf, report_len);
        if (result < 0) {
            perror("Failed to send feature report");
            return;
        }
    }
}
