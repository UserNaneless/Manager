#include "Device.h"
#include <iostream>

Device::~Device() {
    delete deviceInterface;
};

Device::Device(const QDBusObjectPath &path, const QBluetoothDeviceInfo &info, DeviceType type) {
    this->path = path;
    this->info = info;
    this->type = type;

    deviceInterface = new QDBusInterface("org.bluez", path.path(), "org.bluez.Device1", QDBusConnection::systemBus());
    connectProperties();
}

Device::Device() {
}

void Device::setDevice(const QDBusObjectPath &path, const QBluetoothDeviceInfo &info, Device::DeviceType type) {
    this->path = path;
    this->info = info;
    this->type = type;

    deviceInterface = new QDBusInterface("org.bluez", path.path(), "org.bluez.Device1", QDBusConnection::systemBus());
    connectProperties();
}

void Device::onPropertiesChanged(const QString &interface, const QVariantMap &properties, const QStringList &) {

    if(interface == "org.bluez.Device1") {
        if(properties.contains("Connected")) {
            this->type = properties["Connected"].toBool() ? Device::DeviceType::Connected : Device::DeviceType::Paired;
            std::cout << this->type << std::endl;
        }

        if(properties.contains("Paired")) {
            this->type = properties["Paired"].toBool() ? Device::DeviceType::Paired : Device::DeviceType::Discovered;
        }

        emit devicePropertiesChanged();
    }

}

void Device::connectProperties() {
    QDBusConnection::systemBus().connect(
        "org.bluez",
        path.path(),
        "org.freedesktop.DBus.Properties",
        "PropertiesChanged",
        this,
        SLOT(onPropertiesChanged(QString, QVariantMap, QStringList)));
}
