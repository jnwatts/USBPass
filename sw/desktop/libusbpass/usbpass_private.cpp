#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "usbpass_private.h"

USBPass_private::USBPass_private() :
    serial(),
    name(),
    device(NULL)
{
}

void USBPass_private::get_name()
{
    this->name = "";
    if (this->serial.size() == 0)
        return;
    bool wasOpen = true;
    if (this->device == NULL) {
        wasOpen = false;
        this->device = hid_open(USBPASS_VID, USBPASS_PID, this->serial.toStdWString().c_str());
    }
    //TODO: Figure out how to request name?
    if (!wasOpen) {
        hid_close(this->device);
        device = NULL;
    }
}

void USBPass_private::send_large_block(uint8_t id, QByteArray ba)
{
    uint8_t offset = 0;
    uint8_t len = 0;
    while (ba.size() > 0) {
        QByteArray block;
        len = qMin(ba.size(), REPORT_MAX_LENGTH);
        block.append((char)offset);
        block.append((char)len);
        block.append(ba.left(len));
        send_report(id, block);
        ba.remove(0, len);
        offset += len;
    }
}

void USBPass_private::send_report(uint8_t id, QByteArray ba)
{
    if (this->device) {
        int result = 0;
        ba.prepend((char)id);
        printf("_send_report(%d, {%s})\n", id, ba.toHex().constData());
        result = hid_send_feature_report(this->device, (uint8_t*)ba.constData(), ba.size());
        usleep(500 * 1000);
        if (result < 0)
            perror("Failed to send feature report");
    }
}
