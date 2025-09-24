#pragma once
#include "Device.h"
#include <QRegularExpression>
#include <QtDBus>
#include <qbluetoothdevicediscoveryagent.h>
#include <qbluetoothdeviceinfo.h>
#include <qbluetoothlocaldevice.h>
#include <qdbusconnection.h>
#include <qdbusinterface.h>
#include <qdir.h>
#include <qmap.h>
#include <qobject.h>

class Bluetooth : public QObject {
        Q_OBJECT
    private:
        QBluetoothDeviceDiscoveryAgent *discoveryAgent;
        QMap<QString, QBluetoothDeviceInfo> discoveredDevices;
        QMap<QString, QBluetoothDeviceInfo> pairedDevices;
        QMap<QString, QBluetoothDeviceInfo> connectedDevices;

        QDBusConnection bus = QDBusConnection::systemBus();
        QDBusInterface objectManager = QDBusInterface("org.bluez", "/", "org.freedesktop.DBus.ObjectManager", bus);
        QDBusInterface mainPropertiesManager = QDBusInterface("org.bluez", "/org/bluez/hci0", "org.freedesktop.DBus.Properties", bus);

        QString macRegexString = R"(^([0-9A-Fa-f]{2}([:-])){5}[0-9A-Fa-f]{2}$)";
        QRegularExpression macRegex;

    public:
        bool scanning = false;
        bool active = false;

        QList<Device*> devices;
        Device localDevice;

        Bluetooth();
        ~Bluetooth();

        bool turnOnBluetooth();
        bool turnOffBluetooth();
        void connectDevice(const Device *device);


        void startDeviceDiscovery();
        void setupLocalDevice();
        void deviceDiscovered(const QBluetoothDeviceInfo &device);
        void stopDeviceDiscovery();
        void disconnectDevice(const QBluetoothDeviceInfo &device);
        void pairedDevicesChanged(const QBluetoothAddress &address, QBluetoothLocalDevice::Pairing pairing);
        bool isMAC(const QString &mac);
        void handleDeviceConnection(const QBluetoothAddress &address);
        void handleDeviceDisconnection(const QBluetoothAddress &address);

        QMap<QString, QBluetoothDeviceInfo> getPairedDevices();

    signals:
        void newDeviceAdded(const QBluetoothDeviceInfo &device, Device::DeviceType type);
        void newPairedDeviceAdded(const QBluetoothDeviceInfo &device, Device::DeviceType type);
        void newConnectedDeviceAdded(const QBluetoothDeviceInfo &device, Device::DeviceType type);
        void deviceDisconnected(const QBluetoothAddress &address);
        void deviceConnected(const QBluetoothAddress &address);
        void devicePaired(const QBluetoothAddress &address);
};
