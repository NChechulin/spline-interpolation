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

    std::sort(result.points.begin(), result.points.end(), [](QPoint a, QPoint b) {
        return (a.x() < b.x());
    });

    result.check_points();
    return result;
}

void Spline::check_points() const {
    if (this->points.size() <= 2) {
        throw std::length_error("Less than 3 points were provided");
    }

    for (size_t i = 0; i < this->points.size() - 1; ++i) {
        if (points[i].x() == points[i + 1].x()) {
            throw std::range_error("There are at least 2 points with the same X coordinate");
        }
    }
}
