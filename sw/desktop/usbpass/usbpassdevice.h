#ifndef USBPASSDEVICE_H
#define USBPASSDEVICE_H

#include <QObject>
#include <hidapi.h>
#include <stdint.h>

class USBPassDevice : public QObject
{
    Q_OBJECT
public:
    explicit USBPassDevice(QObject *parent = 0);
    ~USBPassDevice(void);

    void open(QString serial_number = "");
    void close(void);

    void set_key(int index, QString key, QString name);
    void set_num_keys(int count);
    void set_quick_key(int key, int index);
    void set_action(int button_id, int action_id);

    void reset(void);

signals:
    
public slots:

private:
    void _send_large_block(uint8_t id, QByteArray data);
    void _send_report(uint8_t id, QByteArray data);

    hid_device *_hid_device;
};

#endif // USBPASSDEVICE_H
