#include "BluetoothItem.h"
#include "LoadQSS.h"

BluetoothItem::BluetoothItem(const QBluetoothDeviceInfo &device) {
    this->device = device;
    layout = new QHBoxLayout(this);
    
    QLabel *name = new QLabel(device.name());
    layout->addWidget(name);

    setMinimumHeight(32);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    setLayout(layout);

    this->name = name;

    setStyleSheet(loadStyles("/home/naneless/Documents/GitHub/Bluetooth/styles/item.qss"));
}


BluetoothItem::~BluetoothItem() {
    delete layout;
    delete name;
}
