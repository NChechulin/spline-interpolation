#ifndef SPLINE_H
#define SPLINE_H

#include <QFileInfo>
#include <QPoint>
#include <vector>

#include "polynomial.h"

class Interpolation {
 private:
  void check_points() const;  // raises exception if something is wrong
 public:
  Interpolation(){};
  static Interpolation FromFile(QString);
  std::vector<QPointF> points;
  std::vector<Polynomial> Interpolate();
};

#endif  // SPLINE_H
