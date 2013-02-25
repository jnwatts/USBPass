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
    void _setEnabled(void);
    void _keyIndexChanged(int index);
    void _keyValueChanged(QString value);
    void _keyNameChanged(QString value);
    void _buttonIndexChagned(int index);
    void _actionIndexChanged(int index);
    void _quickkeyIndexChanged(int index);
    void _qkKeyIndexChanged(int index);
    void _sendToDevice(void);

private:
    struct KeyInfo {
        int index;
        QString name;
        QString value;
        bool modified;
    };

    struct ButtonInfo {
        int button;
        int action;
        bool modified;
    };

    struct QuickkeyInfo {
        int quickIndex;
        int keyIndex;
        bool modified;
    };

    struct ButtonId {
        QString name;
        USBPassDevice::Button_t button;
    };

    struct ActionId {
        QString name;
        USBPassDevice::Action_t action;
    };

    static QMap<int, ButtonId> _buttonIds;
    static QMap<int, ActionId> _actionIds;

    Ui::MainWindow *ui;
    USBPassDevice *_device;
    QList<USBPassDevice*> _devices;

    QMap<int, KeyInfo> _keys;
    QMap<int, ButtonInfo> _buttons;
    QMap<int, QuickkeyInfo> _quickkeys;

};

#endif // MAINWINDOW_H
