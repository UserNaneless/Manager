#pragma once

#include <qbluetoothdeviceinfo.h>
#include <qboxlayout.h>
#include <qlabel.h>
#include <qwidget.h>

class BluetoothItem : public QWidget {
    private:
        QLabel *name;
        QHBoxLayout *layout;
        QBluetoothDeviceInfo device;
        bool connected = false;
        bool paired = false;
    public:
        BluetoothItem(const QBluetoothDeviceInfo &device);
        ~BluetoothItem();
};
