#ifndef SPLINE_H
#define SPLINE_H

#include <polynome.h>
#include <vector>
#include <QPoint>
#include <QFileInfo>

class Spline
{
private:
    std::vector<Polynome> polynomes;
    std::vector<QPoint> points;
public:
    Spline() {};
    static Spline FromFile(QString);
};

#endif // SPLINE_H
