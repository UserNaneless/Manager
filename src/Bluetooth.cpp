#include "Bluetooth.h"
#include <iostream>
#include <qbluetoothdevicediscoveryagent.h>
#include <qcontainerfwd.h>
#include <qdir.h>

void Bluetooth::turnOnBluetooth() {

  if (localDevice.isValid()) {
    localDevice.powerOn();
    localDeviceName = localDevice.name();
  }
}

Bluetooth::Bluetooth() {
  discoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
  connect(discoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
          this, &Bluetooth::deviceDiscovered);
}

Bluetooth::~Bluetooth() { delete discoveryAgent; }

void Bluetooth::startDeviceDiscovery() {
    discoveryAgent->start();
    discoveredDevices.clear();
}

void Bluetooth::deviceDiscovered(const QBluetoothDeviceInfo &device) {
  std::cout << device.name().toStdString() << std::endl;
  QString addr = device.address().toString();
  if (!discoveredDevices.contains(addr)) {
    discoveredDevices[addr] = device;
    emit newDeviceAdded(device);
  }

  auto status = localDevice.pairingStatus(device.address());
  if (status == QBluetoothLocalDevice::Paired ||
      status == QBluetoothLocalDevice::AuthorizedPaired && !pairedDevices.contains(addr)) {
    pairedDevices[addr] = device;
    emit newPairedDeviceAdded(device);
  }
}

void Bluetooth::stopDeviceDiscovery() { discoveryAgent->stop(); }

