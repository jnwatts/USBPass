#ifndef USBPASS_PRIVATE_H
#define USBPASS_PRIVATE_H
#include <hidapi.h>
#include <stdint.h>
#include <QByteArray>
#include <QString>

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

class USBPass_private
{
public:
    USBPass_private();
    void get_name(void);
    void send_large_block(uint8_t id, QByteArray ba);
    void send_report(uint8_t id, QByteArray ba);

    QString serial;
    QString name;
    hid_device *device;
};

#endif // USBPASS_PRIVATE_H
