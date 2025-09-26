#include "BluetoothListModel.h"

BluetoothListModel::BluetoothListModel(Bluetooth *bt, QObject *parent) : QAbstractListModel(parent) {
    this->bt = bt;

    setDevices(bt->getPairedDevices());

    connect(bt, &Bluetooth::deviceDiscovered, this, &BluetoothListModel::addDevice);
}

void BluetoothListModel::setDevices(QList<Device *> devices) {
    beginResetModel();
    this->devices = devices;
    endResetModel();

    for (Device *device : devices) {
        connectDevice(device);
    }
}

void BluetoothListModel::addDevice(Device *device) {
    beginInsertRows(QModelIndex(), devices.size(), devices.size());
    devices.append(device);
    connectDevice(device);
    endInsertRows();
}

void BluetoothListModel::connectDevice(Device *device) {
    connect(device, &Device::devicePropertiesChanged, this, [this, device]() {
        int row = this->devices.indexOf(device);

        if (row >= 0) {
            QModelIndex index = this->index(row);
            emit dataChanged(index, index);
        }
    });
}

int BluetoothListModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return devices.size();
};

QVariant BluetoothListModel::data(const QModelIndex &index, int role) const {
    const Device *device = devices[index.row()];

    if (role == Qt::DisplayRole) {
        return device->info.name();
    } else if (role == Qt::UserRole) {
        return device->type;
    }
    return QVariant();
}
