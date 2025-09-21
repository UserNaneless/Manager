#include "Bluetooth.h"
#include "BluetoothItem.h"
#include "qwidget.h"
#include "qscrollarea.h"
#include <qboxlayout.h>
#include <qlist.h>
#include <LoadQSS.h>

class BluetoothList: public QScrollArea {
    Q_OBJECT
    
    private: 
        Bluetooth* bt;
        QVBoxLayout *layout;
        QList<BluetoothItem*> items;
        QWidget *container;

    public:
        BluetoothList(QWidget *parent);
        ~BluetoothList();
        void addDevice(const QBluetoothDeviceInfo &device);
};
