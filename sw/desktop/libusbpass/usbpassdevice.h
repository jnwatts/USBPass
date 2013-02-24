#ifndef USBPASSDEVICE_H
#define USBPASSDEVICE_H

#include <QObject>
#include <stdint.h>

class USBPassDevice
        : public QObject
{
    Q_OBJECT
public:
    enum Button_t {
        BUTTON_SW1 = 0x00,
        BUTTON_SW2 = 0x01,
        BUTTON_SW3 = 0x02,
        BUTTON_SW1L = 0x80,
        BUTTON_SW2L = 0x81,
        BUTTON_SW3L = 0x82
    };

    enum Action_t {
        ACTION_INVALID,
        ACTION_KEY_UP,
        ACTION_KEY_DOWN,
        ACTION_PASTE_KEY,
        ACTION_PASTE_MODE,
        ACTION_PASTE_QUICK_1,
        ACTION_PASTE_QUICK_2,
        ACTION_PASTE_QUICK_3,
        ACTION_PASTE_QUICK_4,
        ACTION_PASTE_QUICK_5,
        ACTION_PASTE_QUICK_6
    };

    static const int NUM_KEYS;
    static const int NUM_QUICKKEYS;

public:
    explicit USBPassDevice(QString serial = "", QObject *parent = 0);
    ~USBPassDevice(void);

    void open(QString serial_number = "");
    void close(void);

    void set_key(int index, QString key, QString name);
    void set_num_keys(int count);
    void set_quick_key(int quickkey, int keyindex);
    void set_action(Button_t button_id, Action_t action_id);

    QString get_serial(void);
    QString get_name(void);

    void reset(void);

    static QList<USBPassDevice*> enumerate_devices(void);

signals:
    
public slots:

private:
    void *data;
};

#endif // USBPASSDEVICE_H
