#pragma once
#include <qbluetoothlocaldevice.h>
#include <qbluetoothdeviceinfo.h>
#include <qbluetoothdevicediscoveryagent.h>
#include <qmap.h>
#include <qobject.h>
#include <qtmetamacros.h>
#include <qdir.h>

class Bluetooth: public QObject {
    Q_OBJECT
    private: 
        QBluetoothLocalDevice localDevice;
        QBluetoothDeviceDiscoveryAgent *discoveryAgent;
        QString localDeviceName;
        QMap<QString, QBluetoothDeviceInfo> discoveredDevices;
    public:
        Bluetooth();
        ~Bluetooth();

        void turnOnBluetooth();
        void startDeviceDiscovery();
        void deviceDiscovered(const QBluetoothDeviceInfo &device);
        void stopDeviceDiscovery();
        void getPairedDevices();

        QMap<QString, QBluetoothDeviceInfo> pairedDevices;

    signals: 
        void newDeviceAdded(const QBluetoothDeviceInfo &device);
        void newPairedDeviceAdded(const QBluetoothDeviceInfo &device);

};
