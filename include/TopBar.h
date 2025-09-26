#include "Bluetooth.h"
#include <qboxlayout.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qwidget.h>
#include "LoadQSS.h"

class TopBar : public QWidget {
        Q_OBJECT

    private:
        QHBoxLayout *layout;
        QPushButton *scanButton;
        QLabel *title;
        Bluetooth *bt;

    public:
        TopBar(Bluetooth *bt);
        ~TopBar() = default;

        void toggleScan();
};
