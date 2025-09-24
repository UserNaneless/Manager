#include "Bluetooth.h"
#include <iostream>
#include <qbluetoothdevicediscoveryagent.h>
#include <qbluetoothdeviceinfo.h>
#include <qbluetoothlocaldevice.h>
#include <qcontainerfwd.h>
#include <qdbusextratypes.h>
#include <qdbusreply.h>
#include <qdir.h>
#include <string>

bool Bluetooth::turnOnBluetooth() {

    auto on = QVariant::fromValue(QDBusVariant(QVariant::fromValue(true)));
    QDBusReply<void> reply = mainPropertiesManager.call("Set", "org.bluez.Adapter1", "Powered", on);

    if (!reply.isValid()) {
        std::cout << reply.error().message().toStdString() << std::endl;
        return false;
    }

    active = true;
    return true;
}

bool Bluetooth::turnOffBluetooth() {

    auto off = QVariant::fromValue(QDBusVariant(QVariant::fromValue(false)));
    QDBusReply<void> reply = mainPropertiesManager.call("Set", "org.bluez.Adapter1", "Powered", off);

    if (!reply.isValid()) {
        std::cout << reply.error().message().toStdString() << std::endl;
        return false;
    }

    active = false;
    return true;
}

Bluetooth::Bluetooth() {
    macRegex = QRegularExpression(macRegexString);

    setupLocalDevice();

    // if (localDevice.isValid())
    // localDeviceName = localDevice.name();
}

Bluetooth::~Bluetooth() {
    for (auto device : devices) {
        delete device;
    }
    // delete discoveryAgent;
}

QMap<QString, QBluetoothDeviceInfo> Bluetooth::getPairedDevices() {

    QMap<QString, QBluetoothDeviceInfo> devices;

    QDBusMessage msg = objectManager.call("GetManagedObjects");

    if (msg.type() == QDBusMessage::ErrorMessage) {
        std::cout << msg.errorMessage().toStdString() << std::endl;
        return {};
    }

    const QDBusArgument &arg = msg.arguments().at(0).value<QDBusArgument>();

    QMap<QDBusObjectPath, QVariantMap> pairedDevices;

    arg.beginMap();
    while (!arg.atEnd()) {
        QDBusObjectPath path;
        QMap<QString, QVariantMap> interfaces;

        arg.beginMapEntry();
        arg >> path >> interfaces;
        arg.endMapEntry();

        if (interfaces.contains("org.bluez.Device1")) {
            QVariantMap props = interfaces["org.bluez.Device1"];
            if (props.contains("Paired") && props["Paired"].toBool()) {
                pairedDevices.insert(path, props);
            }
        }
    }
    arg.endMap();

    for (auto device = pairedDevices.begin(); device != pairedDevices.end(); device++) {
        QDBusObjectPath path = device.key();
        QVariantMap props = device.value();

        QBluetoothAddress addr = QBluetoothAddress(props.value("Address").toString());
        devices[addr.toString()] = QBluetoothDeviceInfo(addr, props.value("Name").toString(), props.value("Class").toUInt());
        bool connected = props.value("Connected").toBool();
        this->devices.append(new Device(path, QBluetoothDeviceInfo(addr, props.value("Name").toString(), props.value("Class").toUInt()), connected ? Device::DeviceType::Connected : Device::DeviceType::Paired));
    }

    std::cout << std::to_string(pairedDevices.size()) + " paired devices" << std::endl;

    return devices;
}

void Bluetooth::startDeviceDiscovery() {
    // discoveryAgent->start();
    scanning = true;
}

void Bluetooth::connectDevice(const Device *device) {
    if (!active)
        return;

    QDBusReply<void> reply = device->deviceInterface->call("Connect");

    if (!reply.isValid()) {
        std::cout << reply.error().message().toStdString() << std::endl;
        return;
    }
}

void Bluetooth::disconnectDevice(const QBluetoothDeviceInfo &device) {
    // localDevice.requestPairing(device.address(), QBluetoothLocalDevice::Unpaired);
}

void Bluetooth::setupLocalDevice() {

    QDBusReply<QVariantMap> reply = mainPropertiesManager.call("GetAll", "org.bluez.Adapter1");

    if (!reply.isValid()) {
        std::cout << reply.error().message().toStdString() << std::endl;
        return;
    }

    QVariantMap interface = reply.value();

    auto name = interface["Alias"].toString();
    auto bluetoothClass = interface["Class"].toUInt();
    auto address = QBluetoothAddress(interface["Address"].toString());

    localDevice.setDevice(QDBusObjectPath("/org/bluez/hci0"), QBluetoothDeviceInfo(address, name, bluetoothClass));
}

void Bluetooth::deviceDiscovered(const QBluetoothDeviceInfo &device) {
    std::cout << device.name().toStdString() << std::endl;
    QString addr = device.address().toString();

    // if (localDevice.connectedDevices().contains(device.address())) {
    // connectedDevices[addr] = device;
    // emit newConnectedDeviceAdded(device, DeviceType::Connected);
    // return;
    // }

    // auto status = localDevice.pairingStatus(device.address());
    // if (status == QBluetoothLocalDevice::Paired ||
    // status == QBluetoothLocalDevice::AuthorizedPaired && !pairedDevices.contains(addr)) {
    // return;
    // }

    if (!discoveredDevices.contains(addr)) {
        discoveredDevices[addr] = device;
        emit newDeviceAdded(device, Device::DeviceType::Discovered);
    }
}

void Bluetooth::pairedDevicesChanged(const QBluetoothAddress &address, QBluetoothLocalDevice::Pairing pairing) {
    if (pairing == QBluetoothLocalDevice::Paired || pairing == QBluetoothLocalDevice::AuthorizedPaired)
        emit devicePaired(address);
    else
        std::cout << "Unpaired" << std::endl;
}

void Bluetooth::stopDeviceDiscovery() {
    // discoveryAgent->stop();
    scanning = false;
}

bool Bluetooth::isMAC(const QString &mac) {
    return macRegex.match(mac).hasMatch();
}

void Bluetooth::handleDeviceConnection(const QBluetoothAddress &address) {
    emit deviceConnected(address);
}

void Bluetooth::handleDeviceDisconnection(const QBluetoothAddress &address) {
    emit deviceDisconnected(address);
}
