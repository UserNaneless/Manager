#include "Bluetooth.h"
#include "BluetoothItem.h"
#include "BluetoothListModel.h"
#include "DeviceDelegate.h"
#include "DeviceSortFilterProxy.h"
#include "QListView"
#include <LoadQSS.h>
#include <qbluetoothaddress.h>
#include <qbluetoothdeviceinfo.h>
#include <qboxlayout.h>
#include <qlist.h>

class BluetoothList : public QListView {
        Q_OBJECT

    private:
        Bluetooth *bt;
        QList<BluetoothItem *> connectedItems;
        QList<BluetoothItem *> pairedItems;
        QList<BluetoothItem *> discoveredItems;

        BluetoothListModel model;
        DeviceSortFilterProxy proxyModel;
        DeviceDelegate delegate;

        BluetoothItem *findItem(const QBluetoothAddress &address, const QList<BluetoothItem *> &list);
        BluetoothItem *findItem(const QBluetoothDeviceInfo &device, const QList<BluetoothItem *> &list);

        void sortDevices();

    public:
        BluetoothList(Bluetooth *bt);
        ~BluetoothList();
        void addDevice(const QBluetoothDeviceInfo &device, Device::DeviceType type);
        void connectedDevice(const QBluetoothAddress &address);
        void disconnectedDevice(const QBluetoothAddress &address);
        void pairedDevice(const QBluetoothAddress &address);
};
