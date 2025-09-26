#pragma once
#include "Device.h"
#include <QRegularExpression>
#include <QtDBus>
#include <qbluetoothdevicediscoveryagent.h>
#include <qbluetoothdeviceinfo.h>
#include <qbluetoothlocaldevice.h>
#include <qbluetoothuuid.h>
#include <qdbusconnection.h>
#include <qdbusextratypes.h>
#include <qdbusinterface.h>
#include <qdir.h>
#include <qmap.h>
#include <qobject.h>

using Properties = QMap<QString, QVariantMap>;
Q_DECLARE_METATYPE(Properties);

class Bluetooth : public QObject {
        Q_OBJECT
    private:
        QDBusConnection bus = QDBusConnection::systemBus();
        QDBusInterface objectManager = QDBusInterface("org.bluez", "/", "org.freedesktop.DBus.ObjectManager", bus);
        QDBusInterface mainPropertiesManager = QDBusInterface("org.bluez", "/org/bluez/hci0", "org.freedesktop.DBus.Properties", bus);
        QDBusInterface adapterManager = QDBusInterface("org.bluez", "/org/bluez/hci0", "org.bluez.Adapter1", bus);

    public:
        bool scanning = false;
        bool active = false;
        Device localDevice;

        Bluetooth();
        ~Bluetooth();

        bool turnOnBluetooth();
        bool turnOffBluetooth();
        void connectDevice(const Device *device);

        void setupLocalDevice();
        void startDeviceDiscovery();
        void stopDeviceDiscovery();

        QList<Device *> getPairedDevices();

    signals:
        void deviceDiscovered(Device *device);

    public slots:
        void onDeviceDiscovered(const QDBusObjectPath &path, const Properties &props);
};
