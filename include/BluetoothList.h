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
        QList<BluetoothItem *> connectedItems;
        QList<BluetoothItem *> pairedItems;
        QList<BluetoothItem *> discoveredItems;

        BluetoothListModel* model;
        DeviceSortFilterProxy proxyModel;
        DeviceDelegate delegate;

    public:
        BluetoothList(Bluetooth *bt);
        ~BluetoothList();
};
