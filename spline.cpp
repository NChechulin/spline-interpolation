#include "spline.h"
#include <fstream>
#include <QMessageBox>

Spline Spline::FromFile(QString path) {
    Spline result;

    QFile file(path);
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "Error while opening a file", file.errorString());
    }

    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();

        QStringList fields = line.split(' ');
        if (fields.length() == 2)
        {
            QPoint point(fields[0].toDouble(), fields[1].toDouble());

            result.points.push_back(point);
        }
    }

    file.close();
    return result;
}
