#include <QStyledItemDelegate>
#include <qpainter.h>

class DeviceDelegate : public QStyledItemDelegate {
    public:
        DeviceDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

        void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
        QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

};
