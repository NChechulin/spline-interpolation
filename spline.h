#ifndef SPLINE_H
#define SPLINE_H

#include <QFileInfo>
#include <QPoint>
#include <polynome.h>
#include <vector>

class Spline {
private:
    std::vector<Polynome> polynomes;
    void check_points() const; // raises exception if something is wrong
public:
    Spline() {};
    static Spline FromFile(QString);
    std::vector<QPoint> points;
    std::vector<Polynome> Interpolate();
};

#endif // SPLINE_H
