#include "DeviceDelegate.h"
#include "Device.h"

void DeviceDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    painter->save();

    QString name = index.data(Qt::DisplayRole).toString();
    QString type;

    bool hovered = option.state & QStyle::State_MouseOver;

    const auto deviceType = index.data(Qt::UserRole).toInt();
    if (deviceType == Device::DeviceType::Connected) {
        type = "(Connected)";
    } else if (deviceType == Device::DeviceType::Paired) {
        type = "(Paired)";
    } else if (deviceType == Device::DeviceType::Discovered) {
        type = "(Discovered)";
    }

    painter->drawText(option.rect, Qt::AlignLeft | Qt::AlignVCenter, name + " " + type);

    if (hovered) {
        // painter->fillRect(option.rect, QColor("#5962D9"));
        QPen pen(QColor("#5962D9"));
        pen.setWidth(2);
        painter->setPen(pen);
        painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight());
    }

    painter->restore();
}

QSize DeviceDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    return QSize(option.rect.width(), 32);
}
