#pragma once
#include <qbluetoothdeviceinfo.h>
#include <qdbusextratypes.h>
#include <qdbusinterface.h>

class Device : public QObject {
        Q_OBJECT

    private:
        void connectProperties();

    public:
        enum DeviceType { Discovered,
                          Paired,
                          Connected };

        QDBusObjectPath path;
        QBluetoothDeviceInfo info;

        QDBusInterface *deviceInterface = nullptr;

        DeviceType type = Discovered;

        Device(const QDBusObjectPath &path, const QBluetoothDeviceInfo &info, DeviceType type = Discovered);
        Device();
        ~Device();

        void setDevice(const QDBusObjectPath &path, const QBluetoothDeviceInfo &info, DeviceType type = Discovered);


    public slots:
        void onPropertiesChanged(const QString &interface, const QVariantMap &properties, const QStringList &);
    signals: 
        void devicePropertiesChanged();


};
