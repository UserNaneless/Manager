#include "BluetoothList.h"
#include "LoadQSS.h"
#include <qapplication.h>
#include <qmainwindow.h>
#include <qnamespace.h>
#include <qwidget.h>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QMainWindow w;
    w.setAttribute(Qt::WA_TranslucentBackground);

    auto styles = loadStyles("/home/naneless/Documents/GitHub/Bluetooth/styles/main.qss");
    w.setStyleSheet(styles);

    BluetoothList *list = new BluetoothList(&w);

    w.setCentralWidget(list);

    w.resize(300, 300);
    w.show();

    return app.exec();
}
