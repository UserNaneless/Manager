#include "Bluetooth.h"
#include "BluetoothList.h"
#include "LoadQSS.h"
#include "TopBar.h"
#include <QFontDatabase>
#include <qapplication.h>
#include <qboxlayout.h>
#include <qcontainerfwd.h>
#include <qdbusreply.h>
#include <qmainwindow.h>
#include <qnamespace.h>
#include <qwidget.h>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QMainWindow w;
    // w.setAttribute(Qt::WA_TranslucentBackground);

    int fontId = QFontDatabase::addApplicationFont("/home/naneless/Documents/GitHub/Bluetooth/fonts/0xProtoNerdFont-Regular.ttf");
    QString family = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont font(family, 12);
    app.setFont(font);

    QWidget *container = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setContentsMargins(16, 16, 16, 16);

    auto styles = loadStyles("/home/naneless/Documents/GitHub/Bluetooth/styles/main.qss");
    w.setStyleSheet(styles);

    Bluetooth *bt = new Bluetooth();
    bt->turnOnBluetooth();

    TopBar *topBar = new TopBar(bt);

    BluetoothList *list = new BluetoothList(bt);

    layout->addWidget(topBar);
    layout->addWidget(list);

    container->setLayout(layout);
    w.setCentralWidget(container);

    w.resize(300, 300);
    w.show();

    return app.exec();
}
