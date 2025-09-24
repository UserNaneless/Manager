#include "BluetoothList.h"
#include "BluetoothItem.h"
#include "LoadQSS.h"
#include <iostream>
#include <qnamespace.h>

BluetoothList::BluetoothList(Bluetooth *bt) {
    this->bt = bt;

    setMouseTracking(true);
    viewport()->setAttribute(Qt::WA_Hover, true);
    setSpacing(4);

    connect(this->bt, &Bluetooth::newDeviceAdded, this, &BluetoothList::addDevice);
    connect(this->bt, &Bluetooth::newPairedDeviceAdded, this, &BluetoothList::addDevice);
    connect(this->bt, &Bluetooth::newConnectedDeviceAdded, this, &BluetoothList::addDevice);

    connect(this->bt, &Bluetooth::deviceConnected, this, &BluetoothList::connectedDevice);
    connect(this->bt, &Bluetooth::deviceDisconnected, this, &BluetoothList::disconnectedDevice);
    connect(this->bt, &Bluetooth::devicePaired, this, &BluetoothList::pairedDevice);

    setStyleSheet(loadStyles("/home/naneless/Documents/GitHub/Bluetooth/styles/list.qss"));

    auto paired = bt->getPairedDevices();
    for (const auto &device : paired) {
        addDevice(device, Device::DeviceType::Paired);
    }

    model.setDevices(bt->devices);
    proxyModel.setSourceModel(&model);
    proxyModel.setSortRole(Qt::UserRole);
    proxyModel.setDynamicSortFilter(true);
    proxyModel.sort(0, Qt::DescendingOrder);
    setModel(&proxyModel);
    setItemDelegate(&delegate);
}
void BluetoothList::addDevice(const QBluetoothDeviceInfo &device, Device::DeviceType type) {
    // BluetoothItem *item = new BluetoothItem(device, this->bt);
    // item->show();

    // if (type == Bluetooth::DeviceType::Connected) {
    //     connectedItems.append(item);
    //     if (layout->count() == 0)
    //         layout->addWidget(item);
    //     else
    //         layout->insertWidget(0, item);
    // } else if (type == Bluetooth::DeviceType::Paired) {
    //     pairedItems.append(item);
    //     layout->insertWidget(connectedItems.size(), item);
    // } else if (type == Bluetooth::DeviceType::Discovered) {
    //     discoveredItems.append(item);
    //     layout->addWidget(item);
    // }
}

BluetoothItem *BluetoothList::findItem(const QBluetoothDeviceInfo &device, const QList<BluetoothItem *> &items) {
    for (BluetoothItem *item : items) {
        if (item->device.address() == device.address())
            return item;
    }
    return nullptr;
}

BluetoothItem *BluetoothList::findItem(const QBluetoothAddress &address, const QList<BluetoothItem *> &items) {
    for (BluetoothItem *item : items) {
        if (item->device.address() == address)
            return item;
    }
    return nullptr;
}

void BluetoothList::connectedDevice(const QBluetoothAddress &address) {
    /* BluetoothItem *item = findItem(address, pairedItems);
    if (item != nullptr) {
        pairedItems.removeOne(item);
        connectedItems.append(item);

        // layout->insertWidget(0, item);

        item->connected = true;
        item->setName(item->device.name() + " (Connected)");
    } */
}

void BluetoothList::disconnectedDevice(const QBluetoothAddress &address) {
    /* BluetoothItem *item = findItem(address, connectedItems);
    if (item != nullptr) {
        connectedItems.removeOne(item);
        pairedItems.append(item);

        layout->insertWidget(pairedItems.size() - 1, item);

        item->connected = false;
        item->setName(item->device.name() + " (Paired)");
    } */
}

void BluetoothList::pairedDevice(const QBluetoothAddress &address) {
    /* BluetoothItem *item = findItem(address, discoveredItems);
    if (item != nullptr) {
        discoveredItems.removeOne(item);
        pairedItems.append(item);

        // layout->insertWidget(pairedItems.size() - 1, item);

        item->paired = true;
        item->setName(item->device.name() + " (Paired)");
    } */
}

BluetoothList::~BluetoothList() {
    bt->stopDeviceDiscovery();
    delete bt;
}
