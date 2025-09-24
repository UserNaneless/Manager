#include "BluetoothItem.h"
#include "LoadQSS.h"
#include <qnamespace.h>

BluetoothItem::BluetoothItem(const QBluetoothDeviceInfo &device, Bluetooth *bt) {
    this->device = device;
    this->bt = bt;
    layout = new QHBoxLayout(this);

    setAttribute(Qt::WA_Hover, true);
    setMouseTracking(true);
    setAttribute(Qt::WA_StyledBackground, true);

    name = new QLabel(device.name());

    setMinimumHeight(32);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    layout->setContentsMargins(8, 4, 8, 4);
    layout->addWidget(name);
    setLayout(layout);

    connect(this, &BluetoothItem::clicked, this, &BluetoothItem::connectToDevice);

    // paired = bt->localDevice.pairingStatus(device.address()) == QBluetoothLocalDevice::Paired ||
    //          bt->localDevice.pairingStatus(device.address()) == QBluetoothLocalDevice::AuthorizedPaired;
    //
    // if (paired) {
    //     name->setText(device.name() + " (Paired)");
    // }
    //
    // connected = bt->localDevice.connectedDevices().contains(device.address());

    if (connected) {
        name->setText(device.name() + " (Connected)");
    }

    setStyleSheet(loadStyles("/home/naneless/Documents/GitHub/Bluetooth/styles/item.qss"));
}

void BluetoothItem::connectToDevice() {
    // if (!connected)
    // bt->connectDevice(device);
    // else
    // bt->disconnectDevice(device);
}

void BluetoothItem::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        emit clicked();
        QWidget::mousePressEvent(event);
    }
}

void BluetoothItem::setName(const QString &name) {
    this->name->setText(name);
}
