#include "Bluetooth.h"
#include <iostream>
#include <qbluetoothdevicediscoveryagent.h>
#include <qbluetoothdeviceinfo.h>
#include <qbluetoothlocaldevice.h>
#include <qcontainerfwd.h>
#include <qdbusargument.h>
#include <qdbusextratypes.h>
#include <qdbusmetatype.h>
#include <qdbusreply.h>
#include <qdir.h>
#include <string>

Bluetooth::Bluetooth() {
    qDBusRegisterMetaType<Properties>();

    setupLocalDevice();

    QDBusConnection::systemBus().connect(
        "org.bluez",
        "/",
        "org.freedesktop.DBus.ObjectManager",
        "InterfacesAdded",
        this,
        SLOT(onDeviceDiscovered(QDBusObjectPath, Properties)));
}

Bluetooth::~Bluetooth() {
    if (scanning)
        stopDeviceDiscovery();
}

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

QList<Device *> Bluetooth::getPairedDevices() {

    QList<Device *> devices;

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
        bool connected = props.value("Connected").toBool();
        devices.append(new Device(path, QBluetoothDeviceInfo(addr, props.value("Alias").toString(), props.value("Class").toUInt()), connected ? Device::DeviceType::Connected : Device::DeviceType::Paired));
    }

    std::cout << std::to_string(pairedDevices.size()) + " paired devices" << std::endl;

    return devices;
}

void Bluetooth::startDeviceDiscovery() {
    if (!active)
        return;

    QDBusReply<void> reply = adapterManager.call("StartDiscovery");

    if (!reply.isValid()) {
        std::cout << reply.error().message().toStdString() << std::endl;
        return;
    }
    scanning = true;
}

void Bluetooth::stopDeviceDiscovery() {
    if (!active)
        return;

    QDBusReply<void> reply = adapterManager.call("StopDiscovery");

    if (!reply.isValid()) {
        std::cout << reply.error().message().toStdString() << std::endl;
        return;
    }

    scanning = false;
}

void Bluetooth::onDeviceDiscovered(const QDBusObjectPath &path, const Properties &props) {
    std::cout << path.path().toStdString() << std::endl;
    if (props.contains("org.bluez.Device1")) {
        const auto &device = props["org.bluez.Device1"];
        emit deviceDiscovered(new Device(path, QBluetoothDeviceInfo(QBluetoothAddress(device["Address"].toString()), device["Alias"].toString(), device["Class"].toUInt()), Device::DeviceType::Discovered));
    }
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
