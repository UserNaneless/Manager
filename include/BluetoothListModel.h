#pragma once
#include "Device.h"
#include <qabstractitemmodel.h>
#include <qlist.h>
class BluetoothListModel : public QAbstractListModel {
        Q_OBJECT

    public:
        BluetoothListModel(QObject *parent = nullptr);
        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
        void setDevices(QList<Device *> &devices);
        void addDevice(Device *device);
        void connectDevice(Device *device);

    private:
        QList<Device *> devices;
};
