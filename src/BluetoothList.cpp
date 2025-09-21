#include "BluetoothList.h"
#include "BluetoothItem.h"
#include "LoadQSS.h"
#include <iostream>

BluetoothList::BluetoothList(QWidget *parent) : QScrollArea(parent) {
    bt = new Bluetooth();
    layout = new QVBoxLayout();
    container = new QWidget();
    layout->setContentsMargins(16, 32, 16, 32);
    layout->setSpacing(16);
    layout->setAlignment(Qt::AlignTop);
    container->setLayout(layout);

    setWidget(container);
    setWidgetResizable(true);

    connect(bt, &Bluetooth::newDeviceAdded, this, &BluetoothList::addDevice);

    bt->turnOnBluetooth();
    bt->startDeviceDiscovery();

    setStyleSheet(loadStyles("/home/naneless/Documents/GitHub/Bluetooth/styles/list.qss"));
}
void BluetoothList::addDevice(const QBluetoothDeviceInfo &device) {
    BluetoothItem *item = new BluetoothItem(device);
    item->show();
    items.append(item);
    layout->addWidget(item);
}

BluetoothList::~BluetoothList() {
    bt->stopDeviceDiscovery();
    delete bt;
    delete layout;
    delete container;

    for (BluetoothItem *item : items) {
        delete item;
    }
}
