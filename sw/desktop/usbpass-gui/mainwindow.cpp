#include <stdio.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"

#if 0
#define DBG(msg, args...) printf("%s:%d " msg "\n", __func__, __LINE__, ##args)
#else
#define DBG(msg, args...) (void)0
#endif

static const QString OPEN_DEVICE = "&Open device";
static const QString CLOSE_DEVICE = "&Close device";

QMap<int, MainWindow::ButtonId> MainWindow::_buttonIds;
QMap<int, MainWindow::ActionId> MainWindow::_actionIds;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _device(NULL)
{
    ui->setupUi(this);

    if (_buttonIds.size() == 0) {
        ButtonId id;
        int i = 0;

        id.name = "SW1";
        id.button = USBPassDevice::BUTTON_SW1;
        _buttonIds[i++] = id;
        id.name = "SW1 (long)";
        id.button = USBPassDevice::BUTTON_SW1L;
        _buttonIds[i++] = id;
        id.name = "SW2";
        id.button = USBPassDevice::BUTTON_SW2;
        _buttonIds[i++] = id;
        id.name = "SW2 (long)";
        id.button = USBPassDevice::BUTTON_SW2L;
        _buttonIds[i++] = id;
        id.name = "SW3";
        id.button = USBPassDevice::BUTTON_SW3;
        _buttonIds[i++] = id;
        id.name = "SW3 (long)";
        id.button = USBPassDevice::BUTTON_SW3L;
        _buttonIds[i++] = id;
    }

    if (_actionIds.size() == 0) {
        ActionId id;
        int i = 0;

        id.name = "INVALID";
        id.action = USBPassDevice::ACTION_INVALID;
        _actionIds[i++] = id;
        id.name = "KEY_UP";
        id.action = USBPassDevice::ACTION_KEY_UP;
        _actionIds[i++] = id;
        id.name = "KEY_DOWN";
        id.action = USBPassDevice::ACTION_KEY_DOWN;
        _actionIds[i++] = id;
        id.name = "PASTE_KEY";
        id.action = USBPassDevice::ACTION_PASTE_KEY;
        _actionIds[i++] = id;
        id.name = "PASTE_MODE";
        id.action = USBPassDevice::ACTION_PASTE_MODE;
        _actionIds[i++] = id;
        id.name = "PASTE_QUICK_1";
        id.action = USBPassDevice::ACTION_PASTE_QUICK_1;
        _actionIds[i++] = id;
        id.name = "PASTE_QUICK_2";
        id.action = USBPassDevice::ACTION_PASTE_QUICK_2;
        _actionIds[i++] = id;
        id.name = "PASTE_QUICK_3";
        id.action = USBPassDevice::ACTION_PASTE_QUICK_3;
        _actionIds[i++] = id;
        id.name = "PASTE_QUICK_4";
        id.action = USBPassDevice::ACTION_PASTE_QUICK_4;
        _actionIds[i++] = id;
        id.name = "PASTE_QUICK_5";
        id.action = USBPassDevice::ACTION_PASTE_QUICK_5;
        _actionIds[i++] = id;
        id.name = "PASTE_QUICK_6";
        id.action = USBPassDevice::ACTION_PASTE_QUICK_6;
        _actionIds[i++] = id;
    }

    ui->sbKeyIndex->setMinimum(1);
    ui->sbKeyIndex->setMaximum(USBPassDevice::NUM_KEYS);
    ui->sbKeyIndex->setValue(1);

    ui->sbQKIndex->setMinimum(1);
    ui->sbQKIndex->setMaximum(USBPassDevice::NUM_KEYS);
    ui->sbQKIndex->setValue(1);

    ui->cbButton->clear();
    foreach (ButtonId id, _buttonIds) {
        ui->cbButton->addItem(id.name);
        DBG("Added %s", id.name.toUtf8().constData());
    }

    ui->cbAction->clear();
    foreach (ActionId id, _actionIds) {
        ui->cbAction->addItem(id.name);
    }

    connect(ui->pbOpenCloseDevice, SIGNAL(clicked()), this, SLOT(_openCloseDevice()));
    connect(ui->pbSendToDevice, SIGNAL(clicked()), this, SLOT(_sendToDevice()));

    connect(ui->sbKeyIndex, SIGNAL(valueChanged(int)), this, SLOT(_keyIndexChanged(int)));
    connect(ui->tKeyName, SIGNAL(textChanged(QString)), this, SLOT(_keyNameChanged(QString)));
    connect(ui->tKeyValue, SIGNAL(textChanged(QString)), this, SLOT(_keyValueChanged(QString)));

    connect(ui->cbButton, SIGNAL(currentIndexChanged(int)), this, SLOT(_buttonIndexChagned(int)));
    connect(ui->cbAction, SIGNAL(currentIndexChanged(int)), this, SLOT(_actionIndexChanged(int)));


    _initInfo();
    _refreshDevices();
    _setEnabled();
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
        int i = 0;

        info = ButtonInfo();
        info.action = USBPassDevice::ACTION_INVALID;
        info.button = USBPassDevice::BUTTON_SW1;
        info.modified = false;
        _buttons[i++] = info;

        info = ButtonInfo();
        info.action = USBPassDevice::ACTION_INVALID;
        info.button = USBPassDevice::BUTTON_SW2;
        info.modified = false;
        _buttons[i++] = info;

        info = ButtonInfo();
        info.action = USBPassDevice::ACTION_INVALID;
        info.button = USBPassDevice::BUTTON_SW3;
        info.modified = false;
        _buttons[i++] = info;

        info = ButtonInfo();
        info.action = USBPassDevice::ACTION_INVALID;
        info.button = USBPassDevice::BUTTON_SW1L;
        info.modified = false;
        _buttons[i++] = info;

        info = ButtonInfo();
        info.action = USBPassDevice::ACTION_INVALID;
        info.button = USBPassDevice::BUTTON_SW2L;
        info.modified = false;
        _buttons[i++] = info;

        info = ButtonInfo();
        info.action = USBPassDevice::ACTION_INVALID;
        info.button = USBPassDevice::BUTTON_SW3L;
        info.modified = false;
        _buttons[i++] = info;
    }


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
    _setEnabled();
}

void MainWindow::_setEnabled(void)
{
    bool isOpen = (this->_device != NULL);

    ui->cbDevices->setEnabled(!isOpen);
    ui->sbKeyIndex->setEnabled(isOpen);
    ui->tKeyName->setEnabled(isOpen);
    ui->tKeyValue->setEnabled(isOpen);
    ui->cbButton->setEnabled(isOpen);
    ui->cbAction->setEnabled(isOpen);
    ui->cbQuickKey->setEnabled(isOpen);
    ui->sbQKIndex->setEnabled(isOpen);
    ui->pbSendToDevice->setEnabled(isOpen);
}

void MainWindow::_keyIndexChanged(int index)
{
    index--;
    if (_keys.contains(index)) {
        KeyInfo info = _keys[index];
        ui->tKeyName->setText(info.name);
        ui->tKeyValue->setText(info.value);
    } else {
        ui->tKeyName->setText("");
        ui->tKeyValue->setText("");
    }
}

void MainWindow::_keyValueChanged(QString value)
{
    int index = ui->sbKeyIndex->value() - 1;
    QMap<int, KeyInfo>::Iterator info = _keys.find(index);
    if (info != _keys.end()) {
        info.value().value = value;
        info.value().modified = true;
    }
}

void MainWindow::_keyNameChanged(QString value)
{
    int index = ui->sbKeyIndex->value() - 1;
    QMap<int, KeyInfo>::Iterator info = _keys.find(index);
    if (info != _keys.end()) {
        info.value().name = value;
        info.value().modified = true;
    }
}

void MainWindow::_buttonIndexChagned(int index)
{
    QMap<int, ButtonInfo>::Iterator info = _buttons.find(index);
    if (info != _buttons.end()) {
        ui->cbAction->setCurrentIndex(info.value().action);
    }
}

void MainWindow::_actionIndexChanged(int index)
{
    int buttonIndex = ui->cbButton->currentIndex();
    int actionIndex = index;
    QMap<int, ButtonInfo>::Iterator info = _buttons.find(buttonIndex);
    if (info != _buttons.end()) {
        info.value().action = actionIndex;
        info.value().modified = true;
    }
}

void MainWindow::_quickkeyIndexChanged(int index)
{
    QMap<int, QuickkeyInfo>::Iterator info = _quickkeys.find(index);
    if (info != _quickkeys.end()) {
        ui->sbQKIndex->setValue(info.value().keyIndex);
    }
}

void MainWindow::_qkKeyIndexChanged(int index)
{
    int quickIndex = ui->cbQuickKey->currentIndex();
    int keyIndex = index - 1;
    QMap<int, QuickkeyInfo>::Iterator info = _quickkeys.find(quickIndex);
    if (info != _quickkeys.end()) {
        info.value().keyIndex = keyIndex;
        info.value().modified = true;
    }
}

void MainWindow::_sendToDevice(void)
{
    QMap<int, KeyInfo>::Iterator keyInfo;
    QMap<int, QuickkeyInfo>::Iterator quickkeyInfo;
    QMap<int, ButtonInfo>::Iterator buttonInfo;

    _device->open();

    for (keyInfo = _keys.begin(); keyInfo != _keys.end(); keyInfo++) {
        if (keyInfo.value().modified) {
            DBG("keyInfo: index=%d, value=%s, name=%s", keyInfo.value().index, keyInfo.value().value.toUtf8().constData(), keyInfo.value().name.toUtf8().constData());
            this->_device->set_key(keyInfo.value().index, keyInfo.value().value, keyInfo.value().name);
            keyInfo.value().modified = false;
        }
    }

    for (quickkeyInfo = _quickkeys.begin(); quickkeyInfo != _quickkeys.end(); quickkeyInfo++) {
        if (quickkeyInfo.value().modified) {
            DBG("quickkeyInfo: quickIndex=%d, keyIndex=%d", quickkeyInfo.value().quickIndex, quickkeyInfo.value().keyIndex);
            this->_device->set_quick_key(quickkeyInfo.value().quickIndex, quickkeyInfo.value().keyIndex);
            quickkeyInfo.value().modified = false;
        }
    }

    for (buttonInfo = _buttons.begin(); buttonInfo != _buttons.end(); buttonInfo++) {
        if (buttonInfo.value().modified) {
            DBG("buttonInfo: button=%x, action=%x", _buttonIds[buttonInfo.value().button].button, _actionIds[buttonInfo.value().action].action);
            this->_device->set_action(_buttonIds[buttonInfo.value().button].button, _actionIds[buttonInfo.value().action].action);
            buttonInfo.value().modified = false;
        }
    }

    _device->reset();
    _device->close();

}


