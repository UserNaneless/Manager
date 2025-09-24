#include "TopBar.h"
#include <qnamespace.h>

TopBar::TopBar(Bluetooth *bt) {
    this->bt = bt;

    layout = new QHBoxLayout(this);

    scanButton = new QPushButton("Scan");
    title = new QLabel(bt->localDevice.info.name());

    scanButton->setMaximumWidth(120);
    scanButton->setMinimumHeight(32);
    scanButton->setCursor(Qt::PointingHandCursor);

    layout->addWidget(title);
    layout->addWidget(scanButton);

    this->setLayout(layout);

    connect(scanButton, &QPushButton::clicked, this, &TopBar::toggleScan);

    setStyleSheet(loadStyles("/home/naneless/Documents/GitHub/Bluetooth/styles/topbar.qss"));
}

void TopBar::toggleScan() {
    if (bt->scanning) {
        bt->stopDeviceDiscovery();
        scanButton->setText("Scan");
    } else {
        bt->startDeviceDiscovery();
        scanButton->setText("Stop");
    }
}
