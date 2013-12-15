#include <stdlib.h>
#include <stdio.h>
#include <hidapi.h>
#include <wchar.h>
#include <string>
#include "usbpass_private.h"
#include "usbpassdevice.h"

#if 0
#define DBG(msg, args...) printf("%s:%d " msg "\n", __func__, __LINE__, ##args)
#else
#define DBG(msg, args...) (void)0
#endif
#define toPrivate(data) ((USBPass_private*)(data))

const int USBPassDevice::NUM_KEYS = 20;
const int USBPassDevice::NUM_QUICKKEYS = 6;

USBPassDevice::USBPassDevice(std::string serial)
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

void USBPassDevice::open(std::string serial_number)
{
    DBG();
    USBPass_private *data = toPrivate(this->data);
    if (data->device)
        return;
    if (serial_number.size() > 0) {
        std::wstring _serial_number = std::wstring(serial_number.begin(), serial_number.end());
        data->device = hid_open(USBPASS_VID, USBPASS_PID, _serial_number.c_str());
    } else {
        data->device = hid_open(USBPASS_VID, USBPASS_PID, NULL);
    }
    if (data->device == NULL) {
        perror("Failed to open device");
        return;
    }
}

void USBPassDevice::close()
{
    DBG();
    USBPass_private *data = toPrivate(this->data);
    if (data->device) {
        hid_close(data->device);
        data->device = NULL;
    }
}

void USBPassDevice::set_key(int index, std::string key, std::string name)
{
    DBG();
    USBPass_private *data = toPrivate(this->data);
    data->send_report_string(REPORT_ID_SET_KEY, key);
    data->send_report_string(REPORT_ID_SET_NAME, name);
    data->send_report_byte(REPORT_ID_COMMIT_KEY, index);
}

void USBPassDevice::set_num_keys(int count)
{
    DBG();
    USBPass_private *data = toPrivate(this->data);
    data->send_report_byte(REPORT_ID_SET_NUM_KEYS, count);
}

void USBPassDevice::set_quick_key(int quickkey, int keyindex)
{
    DBG();
    USBPass_private *data = toPrivate(this->data);
    char buf[2] = {(char)quickkey, (char)keyindex};
    data->send_report(REPORT_ID_SET_QUICK_KEY, buf, sizeof(buf));
}

void USBPassDevice::set_action(Button_t button_id, Action_t action_id)
{
    DBG();
    USBPass_private *data = toPrivate(this->data);
    char buf[2] = {(char)button_id, (char)action_id};
    data->send_report(REPORT_ID_SET_ACTION, buf, sizeof(buf));
}

std::string USBPassDevice::get_serial()
{
    DBG();
    USBPass_private *data = toPrivate(this->data);
    return data->serial;
}

std::string USBPassDevice::get_name()
{
    DBG();
    USBPass_private *data = toPrivate(this->data);
    if (data->name.size() != 0)
        return data->name;
    else
        return data->serial;
}

void USBPassDevice::reset()
{
    DBG();
    USBPass_private *data = toPrivate(this->data);
    data->send_report(REPORT_ID_RESET, NULL, 0);
}

std::list<USBPassDevice *> USBPassDevice::enumerate_devices(void)
{
    DBG();
    USBPassDevice *device;
    std::list<USBPassDevice*> devices;
    hid_device_info *device_info;
    hid_device_info *info;

    device_info = hid_enumerate(USBPASS_VID, USBPASS_PID);
    info = device_info;
    while (info) {
        std::wstring wstr(device_info->serial_number);
        device = new USBPassDevice(std::string(wstr.begin(), wstr.end()));
        devices.push_back(device);
        info = info->next;
    }
    hid_free_enumeration(device_info);

    return devices;
}
