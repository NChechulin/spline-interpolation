#ifndef SPLINE_H
#define SPLINE_H

#include <QFileInfo>
#include <QPoint>
#include <polynome.h>
#include <vector>

class Interpolation {
private:
    void check_points() const; // raises exception if something is wrong
public:
    Interpolation() {};
    static Interpolation FromFile(QString);
    std::vector<QPoint> points;
    std::vector<Polynome> Interpolate();
};

#endif // SPLINE_H
