#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QMap>
#include <usbpassdevice.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void _initInfo(void);
    void _refreshDevices(void);
    void _freeDevices(void);
    void _openCloseDevice(void);
    void _keyIndexChanged(void);
    void _keyValueChanged(void);
    void _keyNameChanged(void);
    void _quickkeyIndexChanged(void);
    void _actionChanged(void);
    void _sendToDevice(void);

private:
    struct KeyInfo {
        int index;
        QString name;
        QString value;
        bool modified;
    };

    struct ButtonInfo {
        USBPassDevice::Button_t button;
        USBPassDevice::Action_t action;
        bool modified;
    };

    struct QuickkeyInfo {
        int quickIndex;
        int keyIndex;
        bool modified;
    };

    Ui::MainWindow *ui;
    USBPassDevice *_device;
    QList<USBPassDevice*> _devices;

    QMap<int, KeyInfo> _keys;
    QMap<USBPassDevice::Button_t, ButtonInfo> _buttons;
    QMap<int, QuickkeyInfo> _quickkeys;

};

#endif // MAINWINDOW_H
