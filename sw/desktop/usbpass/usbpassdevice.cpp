#include <stdlib.h>
#include <stdio.h>
#include "usbpassdevice.h"

#define USBPASS_VID 0x03eb
#define USBPASS_PID 0x2061

#define REPORT_ID_SET_KEY 1
#define REPORT_ID_SET_NAME 2
#define REPORT_ID_COMMIT_KEY 3
#define REPORT_ID_SET_NUM_KEYS 4
#define REPORT_ID_SET_QUICK_KEY 5
#define REPORT_ID_SET_ACTION 6
#define REPORT_ID_RESET 0xFF

#define REPORT_MAX_LENGTH 60


USBPassDevice::USBPassDevice(QObject *parent) :
    QObject(parent),
    _hid_device(NULL)
{
}

USBPassDevice::~USBPassDevice()
{
    this->close();
}

void USBPassDevice::open(QString serial_number)
{
    if (this->_hid_device)
        return;
    const wchar_t *_serial_number = NULL;
    if (serial_number.size() > 0) {
        _serial_number = serial_number.toStdWString().c_str();
    }
    this->_hid_device = hid_open(USBPASS_VID, USBPASS_PID, _serial_number);
    if (this->_hid_device == NULL) {
        perror("Failed to open device");
        return;
    }
}

void USBPassDevice::close()
{
    if (this->_hid_device) {
        hid_close(this->_hid_device);
        this->_hid_device = NULL;
    }
}

void USBPassDevice::set_key(int index, QString key, QString name)
{
    QByteArray data;
    _send_large_block(REPORT_ID_SET_KEY, key.toAscii());
    _send_large_block(REPORT_ID_SET_NAME, name.toAscii());
    data.append((char)index);
    _send_report(REPORT_ID_COMMIT_KEY, data);
}

void USBPassDevice::set_num_keys(int count)
{
    QByteArray data;
    data.append((char)count);
    _send_report(REPORT_ID_SET_NUM_KEYS, data);
}

void USBPassDevice::set_quick_key(int key, int index)
{
    QByteArray data;
    data.append((char)key);
    data.append((char)index);
    _send_report(REPORT_ID_SET_QUICK_KEY, data);
}

void USBPassDevice::set_action(int button_id, int action_id)
{
    QByteArray data;
    data.append((char)button_id);
    data.append((char)action_id);
    _send_report(REPORT_ID_SET_ACTION, data);
}

void USBPassDevice::reset()
{
    _send_report(REPORT_ID_RESET, QByteArray());
}

void USBPassDevice::_send_large_block(uint8_t id, QByteArray data)
{
    uint8_t offset = 0;
    uint8_t len = 0;
    while (data.size() > 0) {
        QByteArray block;
        len = qMin(data.size(), REPORT_MAX_LENGTH);
        block.append((char)offset);
        block.append((char)len);
        block.append(data.left(len));
        _send_report(id, block);
        data.remove(0, len);
        offset += len;
    }
}

void USBPassDevice::_send_report(uint8_t id, QByteArray data)
{
    if (this->_hid_device) {
        int result = 0;
        data.prepend((char)id);
        printf("_send_report(%d, {%s})\n", id, data.toHex().constData());
        result = hid_send_feature_report(this->_hid_device, (uint8_t*)data.constData(), data.size());
        usleep(500 * 1000);
        if (result < 0)
            perror("Failed to send feature report");
    }
}
