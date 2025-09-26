#pragma once

#include "Bluetooth.h"
#include <QMouseEvent>
#include <qbluetoothdeviceinfo.h>
#include <qboxlayout.h>
#include <qlabel.h>
#include <qwidget.h>

class BluetoothItem : public QWidget {
        Q_OBJECT
    private:
        Bluetooth *bt;
        QLabel *name;
        QHBoxLayout *layout;

    protected:
        void mousePressEvent(QMouseEvent *event) override;
    public:
        bool connected = false;
        bool paired = false;
        QBluetoothDeviceInfo device;

        BluetoothItem(const QBluetoothDeviceInfo &device, Bluetooth *bt);
        ~BluetoothItem() = default;

        void connectToDevice();
        void setName(const QString &name);
    signals:
        void clicked();
};
