#include "mainwindow.h"
#include "ui_mainwindow.h"

static const QString OPEN_DEVICE = "&Open device";
static const QString CLOSE_DEVICE = "&Close device";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->sbKeyIndex->setMinimum(1);
    ui->sbKeyIndex->setMaximum(6);
    ui->sbKeyIndex->setValue(1);

    connect(ui->pbOpenCloseDevice, SIGNAL(clicked()), this, SLOT(_openCloseDevice()));
    connect(ui->pbSendToDevice, SIGNAL(clicked()), this, SLOT(_sendToDevice()));

    _initInfo();
    _refreshDevices();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::_initInfo()
{
    int i = 0;

    for (i = 0; i < USBPassDevice::NUM_KEYS; i++) {
        KeyInfo info;
        info.index = i;
        info.name = "";
        info.value = "";
        info.modified = false;
        _keys[i] = info;
    }

    for (i = 0; i < USBPassDevice::NUM_QUICKKEYS; i++) {
        QuickkeyInfo info;
        info.quickIndex = i;
        info.keyIndex = 0;
        info.modified = false;
        _quickkeys[i] = info;
    }

    {
        ButtonInfo info;

        info = ButtonInfo();
        info.action = USBPassDevice::ACTION_INVALID;
        info.button = USBPassDevice::BUTTON_SW1;
        info.modified = false;
        _buttons[USBPassDevice::BUTTON_SW1] = info;

        info = ButtonInfo();
        info.action = USBPassDevice::ACTION_INVALID;
        info.button = USBPassDevice::BUTTON_SW2;
        info.modified = false;
        _buttons[USBPassDevice::BUTTON_SW2] = info;

        info = ButtonInfo();
        info.action = USBPassDevice::ACTION_INVALID;
        info.button = USBPassDevice::BUTTON_SW3;
        info.modified = false;
        _buttons[USBPassDevice::BUTTON_SW3] = info;

        info = ButtonInfo();
        info.action = USBPassDevice::ACTION_INVALID;
        info.button = USBPassDevice::BUTTON_SW1L;
        info.modified = false;
        _buttons[USBPassDevice::BUTTON_SW1L] = info;

        info = ButtonInfo();
        info.action = USBPassDevice::ACTION_INVALID;
        info.button = USBPassDevice::BUTTON_SW2L;
        info.modified = false;
        _buttons[USBPassDevice::BUTTON_SW2L] = info;

        info = ButtonInfo();
        info.action = USBPassDevice::ACTION_INVALID;
        info.button = USBPassDevice::BUTTON_SW3L;
        info.modified = false;
        _buttons[USBPassDevice::BUTTON_SW3L] = info;
    }

    ui->cbAction->addItem("INVALID", USBPassDevice::ACTION_INVALID);
    ui->cbAction->addItem("KEY_UP", USBPassDevice::ACTION_KEY_UP);
    ui->cbAction->addItem("KEY_DOWN", USBPassDevice::ACTION_KEY_DOWN);
    ui->cbAction->addItem("PASTE_KEY", USBPassDevice::ACTION_PASTE_KEY);
    ui->cbAction->addItem("PASTE_MODE", USBPassDevice::ACTION_PASTE_MODE);
    ui->cbAction->addItem("PASTE_QUICK_1", USBPassDevice::ACTION_PASTE_QUICK_1);
    ui->cbAction->addItem("PASTE_QUICK_2", USBPassDevice::ACTION_PASTE_QUICK_2);
    ui->cbAction->addItem("PASTE_QUICK_3", USBPassDevice::ACTION_PASTE_QUICK_3);
    ui->cbAction->addItem("PASTE_QUICK_4", USBPassDevice::ACTION_PASTE_QUICK_4);
    ui->cbAction->addItem("PASTE_QUICK_5", USBPassDevice::ACTION_PASTE_QUICK_5);
    ui->cbAction->addItem("PASTE_QUICK_6", USBPassDevice::ACTION_PASTE_QUICK_6);
}

void MainWindow::_refreshDevices()
{
    USBPassDevice *device = NULL;
    _freeDevices();
    _devices = USBPassDevice::enumerate_devices();
    foreach (device, _devices) {
        ui->cbDevices->addItem(device->get_name());
    }
}

void MainWindow::_freeDevices()
{
    USBPassDevice *device = NULL;
    ui->cbDevices->clear();
    foreach (device, _devices) {
        delete device;
    }
    _devices.clear();
}

void MainWindow::_openCloseDevice()
{
    if (_device == NULL) {
        // Open device
        int i = ui->cbDevices->currentIndex();
        if (i >= _devices.size())
            return;
        _device = _devices[i];
        ui->pbOpenCloseDevice->setText(CLOSE_DEVICE);
    } else {
        // Close device
        _device->close();
        _device = NULL;
        ui->pbOpenCloseDevice->setText(OPEN_DEVICE);
    }
}

void MainWindow::_keyIndexChanged()
{
    int index = ui->sbKeyIndex->value();
    if (_keys.contains(index)) {
        KeyInfo info = _keys[index];
        ui->tKeyName->setText(info.name);
        ui->tKeyValue->setText(info.value);
    } else {
        ui->tKeyName->setText("");
        ui->tKeyValue->setText("");
    }
}

void MainWindow::_keyValueChanged()
{
    int index = ui->sbKeyIndex->value();
    if (_keys.contains(index)) {
        KeyInfo info = _keys[index];
        info.value = ui->tKeyValue->text();
        info.modified = true;
    }
}

void MainWindow::_keyNameChanged()
{
    int index = ui->sbKeyIndex->value();
    if (_keys.contains(index)) {
        KeyInfo info = _keys[index];
        info.name = ui->tKeyName->text();
        info.modified = true;
    }
}

void MainWindow::_quickkeyIndexChanged()
{
//    int index = ui->sbQKIndex->value();
//    if (_quickkeys.contains(index)) {
//        QuickkeyInfo info = _quickkeys[index];
//    }

}

void MainWindow::_actionChanged()
{
}

void MainWindow::_sendToDevice()
{
    KeyInfo keyInfo;
    QuickkeyInfo quickkeyInfo;
    ButtonInfo buttonInfo;

    _device->open();

    foreach (keyInfo, _keys) {
        if (keyInfo.modified) {
            this->_device->set_key(keyInfo.index, keyInfo.value, keyInfo.name);
            keyInfo.modified = false;
        }
    }

    foreach (quickkeyInfo, _quickkeys) {
        if (quickkeyInfo.modified) {
            this->_device->set_quick_key(quickkeyInfo.quickIndex, quickkeyInfo.keyIndex);
            quickkeyInfo.modified = false;
        }
    }

    foreach (buttonInfo, _buttons) {
        if (buttonInfo.modified) {
            this->_device->set_action(buttonInfo.button, buttonInfo.action);
            buttonInfo.modified = false;
        }
    }
}


