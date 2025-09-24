#pragma once
#include <qsortfilterproxymodel.h>

class DeviceSortFilterProxy : public QSortFilterProxyModel {
        Q_OBJECT
    public:
        DeviceSortFilterProxy(QObject *parent = nullptr) : QSortFilterProxyModel(parent) {};
        ~DeviceSortFilterProxy() = default;

    protected: 
        bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const override {
            int leftDeviceType = sourceModel()->data(source_left, Qt::UserRole).toInt();
            int rightDeviceType = sourceModel()->data(source_right, Qt::UserRole).toInt();

            if(leftDeviceType != rightDeviceType) {
                return leftDeviceType < rightDeviceType;
            }

            QString leftName = sourceModel()->data(source_left, Qt::DisplayRole).toString();
            QString rightName = sourceModel()->data(source_right, Qt::DisplayRole).toString();
            return leftName > rightName;
        };
};
