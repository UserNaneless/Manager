#pragma once

#include <iostream>
#include <qdir.h>
#include <qobject.h>



inline QString loadStyles(const QString &path) {
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cout << "Can't open file: " << path.toStdString() << std::endl;
        return QString();
    }
    return QString::fromUtf8(file.readAll());
}
