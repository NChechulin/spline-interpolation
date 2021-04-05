#include "polynomial.h"

#include <cmath>

Polynomial::Polynomial() : a(0), b(0), c(0), d(0) {}

Polynomial::Polynomial(double a, double b, double c, double d)
    : a(a), b(b), c(c), d(d) {}

Polynomial Polynomial::GetDerivative() const {
  return Polynomial(0, 3 * a, 2 * b, c);
}

double Polynomial::GetValue(double x) const {
  return a * std::pow(x, 3) + b * std::pow(x, 2) + c * x + d;
}
