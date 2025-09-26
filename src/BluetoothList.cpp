#include "BluetoothList.h"
#include "LoadQSS.h"
#include <qnamespace.h>

BluetoothList::BluetoothList(Bluetooth *bt) {
    setMouseTracking(true);
    viewport()->setAttribute(Qt::WA_Hover, true);

    setSpacing(4);

    setStyleSheet(loadStyles("/home/naneless/Documents/GitHub/Bluetooth/styles/list.qss"));

    model = new BluetoothListModel(bt);
    proxyModel.setSourceModel(model);
    proxyModel.setSortRole(Qt::UserRole);
    proxyModel.setDynamicSortFilter(true);
    proxyModel.sort(0, Qt::DescendingOrder);
    setModel(&proxyModel);
    setItemDelegate(&delegate);
}

BluetoothList::~BluetoothList() {
    delete model;
};
