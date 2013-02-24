#include <stdlib.h>
#include <stdio.h>
#include <hidapi.h>
#include "usbpass_private.h"
#include "usbpassdevice.h"


#define toPrivate(data) ((USBPass_private*)(data))

const int USBPassDevice::NUM_KEYS = 20;
const int USBPassDevice::NUM_QUICKKEYS = 6;

USBPassDevice::USBPassDevice(QString serial, QObject *parent) :
    QObject(parent)
{
    USBPass_private *private_data = new USBPass_private();
    data = (void*)private_data;
    private_data->serial = serial;
    private_data->get_name();
}

USBPassDevice::~USBPassDevice()
{
    this->close();
    delete toPrivate(this->data);
}

void USBPassDevice::open(QString serial_number)
{
    USBPass_private *data = toPrivate(this->data);
    if (data->device)
        return;
    const wchar_t *_serial_number = NULL;
    if (serial_number.size() == 0 && data->serial.size() > 0) {
        serial_number = data->serial;
    }
    if (serial_number.size() > 0) {
        _serial_number = serial_number.toStdWString().c_str();
    }
    data->device = hid_open(USBPASS_VID, USBPASS_PID, _serial_number);
    if (data->device == NULL) {
        perror("Failed to open device");
        return;
    }
}

void USBPassDevice::close()
{
    USBPass_private *data = toPrivate(this->data);
    if (data->device) {
        hid_close(data->device);
        data->device = NULL;
    }
}

void USBPassDevice::set_key(int index, QString key, QString name)
{
    USBPass_private *data = toPrivate(this->data);
    QByteArray ba;
    data->send_large_block(REPORT_ID_SET_KEY, key.toAscii());
    data->send_large_block(REPORT_ID_SET_NAME, name.toAscii());
    ba.append((char)index);
    data->send_report(REPORT_ID_COMMIT_KEY, ba);
}

void USBPassDevice::set_num_keys(int count)
{
    USBPass_private *data = toPrivate(this->data);
    QByteArray ba;
    ba.append((char)count);
    data->send_report(REPORT_ID_SET_NUM_KEYS, ba);
}

void USBPassDevice::set_quick_key(int quickkey, int keyindex)
{
    USBPass_private *data = toPrivate(this->data);
    QByteArray ba;
    ba.append((char)quickkey);
    ba.append((char)keyindex);
    data->send_report(REPORT_ID_SET_QUICK_KEY, ba);
}

void USBPassDevice::set_action(Button_t button_id, Action_t action_id)
{
    USBPass_private *data = toPrivate(this->data);
    QByteArray ba;
    ba.append((char)button_id);
    ba.append((char)action_id);
    data->send_report(REPORT_ID_SET_ACTION, ba);
}

QString USBPassDevice::get_serial()
{
    USBPass_private *data = toPrivate(this->data);
    return data->serial;
}

QString USBPassDevice::get_name()
{
    USBPass_private *data = toPrivate(this->data);
    if (data->name.size() != 0)
        return data->name;
    else
        return data->serial;
}

void USBPassDevice::reset()
{
    USBPass_private *data = toPrivate(this->data);
    data->send_report(REPORT_ID_RESET, QByteArray());
}

QList<USBPassDevice *> USBPassDevice::enumerate_devices()
{
    USBPassDevice *device;
    QList<USBPassDevice*> devices;
    hid_device_info *device_info;
    hid_device_info *info;

    device_info = hid_enumerate(USBPASS_VID, USBPASS_PID);
    info = device_info;
    while (info) {
        device = new USBPassDevice(QString::fromWCharArray(device_info->serial_number));
        devices.push_back(device);
        info = info->next;
    }
    hid_free_enumeration(device_info);

    return devices;
}
